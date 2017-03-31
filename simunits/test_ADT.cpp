#include <iostream>

#include <mach7/type_switchN-patterns.hpp> // Support for N-ary Match statement on patterns
#include <mach7/patterns/address.hpp>      // Address and dereference combinators
#include <mach7/patterns/bindings.hpp>     // Mach7 support for bindings on arbitrary UDT
#include <mach7/patterns/constructor.hpp>  // Support for constructor patterns
#include <mach7/patterns/equivalence.hpp>  // Equivalence combinator +
#include <mach7/patterns/primitive.hpp>    // Wildcard, variable and value patterns

struct Element { virtual ~Element() {} };
struct Access : Element { virtual ~Access() {} };
struct IdnUse : Access {
  std::string name;
  IdnUse(const char* n) : name(n) {}
};
struct Dot : Access {
  Access* ref;
  IdnUse* idnUse;
  Dot(Access* r, IdnUse* i) : ref(r), idnUse(i) {}
};
struct Port : Element {
  std::string name;
  Port(const char* n) : name(n) {}
};
struct Simunit : Element {
  std::string name;
  std::vector<Port*>*  ports;
  double getReal() {return 2.3;}
  Simunit(const char* n, std::vector<Port*>*  p) : name(n), ports(p) {}
};
struct Connection : Element {
  Access* port_a;
  Access* port_b;
  Connection(Access* a, Access* b) : port_a(a), port_b(b) {}
};
struct System : Simunit {
  // std::string name; // from Simunit
  // std::vector<Port*>* ports; // from Simunit
  std::vector<Simunit*>* simunits;
  std::vector<Connection*>* connections;
  System(const char* n, std::vector<Port*>* p, std::vector<Simunit*>* s, std::vector<Connection*>* c)
    : Simunit(n,p), simunits(s), connections(c) {}
};

//------------------------------------------------------------------------------

namespace mch ///< Mach7 library namespace
{
template <> struct bindings<IdnUse> { Members(IdnUse::name); };
template <> struct bindings<Dot> { Members(Dot::ref, Dot::idnUse); };
template <> struct bindings<Port> { Members(Port::name); };
template <> struct bindings<Simunit> { Members(Simunit::name, Simunit::ports); };
template <> struct bindings<Connection> { Members(Connection::port_a, Connection::port_b); };
template <> struct bindings<System> { Members(System::name, System::ports, System::simunits, System::connections);  };
} // of namespace mch


//------------------------------------------------------------------------------

using namespace mch; // Enable use of pattern-matching constructs without namespace qualification

std::ostream& operator<<(std::ostream& os, const Element& t) {
  std::string      str;
  var<const Port&>  pa, pb;
  var<const Simunit&> sim;
  var<const System&> sys;
  var<const std::vector<Port*>&> ps;
  var<const std::vector<Simunit*>&> sims;
  var<const std::vector<Connection*>&> cns;
  var<const IdnUse&> idn1;
  var<const Access&> a1, a2;
  var<const Element&> t1,t2;


  Match(t) {
    Case(C<Port>(str))       return os << "Port(name=" << str << ')';
    Case(C<IdnUse>(str))     return os << "IdnUse(name=" << str << ')';
    Case(C<Dot>(a1, idn1))   return os << "Dot(ref=" << a1 << ", idnUse=" << idn1 << ')';
    Case(C<Connection>(&a1,&a2))  {
      return os << "Connection(port_a=" << a1 << ", port_b=" << a2 << ")";
    }
    Case(C<System>(str,&ps,&sims,&cns)) {
      auto ports = ps.m_value;
      auto simunits = sims.m_value;
      auto connections = cns.m_value;
      os << "System(name=" << str << ", ports={";
      for (auto i = ports->begin(); i != ports->end(); i++) {
        if (i != ports->begin()) os << ", ";
        os << *(*i);
      }
      os << "}, simunits={";
      for (auto i = simunits->begin(); i != simunits->end(); i++) {
        if (i != simunits->begin()) os << ", ";
        os << *(*i);
      }
      os << "}, connections={";
      for (auto i = connections->begin(); i != connections->end(); i++) {
        if (i != connections->begin()) os << ", ";
        os << *(*i);
      }
      return os << "})";
    }
    // "Simunit" matches also "System" => match after "System"!
    Case(C<Simunit>(str,&ps))  {
      auto ports = ps.m_value;
      os << "Simunit(name=" << str << ", ports={";
      for (auto i = ports->begin(); i != ports->end(); i++) {
        if (i != ports->begin()) os << ", ";
        os << *(*i);
      }
      return os << "})";
    }

  }
  EndMatch

  return os; // To prevent all control path warning
}

// maintain a symbol table which keeps the concrete classes?
struct symboltable {
  // (name, simunitVariant[FMU20ME, FMU20CS, TLM])
  // (name, portVariant[ScalarRealOutput, ScalarRealInput])
  // std::map<symboltable>* nested;
};

int main() {
  //Element* e = new Simunit("myname", new std::vector<Port*>({new Port("asdf"), new Port("fdsa")}));
  Element* e = new System("mysystem",
    new std::vector<Port*>({new Port("p1")}),
    new std::vector<Simunit*>({
      new Simunit("mysimunit", new std::vector<Port*>({
        new Port("ou1"),
        new Port("out2")
      }))
    }),
    new std::vector<Connection*>({
      new Connection(new Dot(new IdnUse("mysimunit"), new IdnUse("out1")), new IdnUse("p1"))
    })
  );
  std::cout << *e << std::endl;
}
