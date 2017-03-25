#include <iostream>

#include <mach7/type_switchN-patterns.hpp> // Support for N-ary Match statement on patterns
#include <mach7/patterns/address.hpp>      // Address and dereference combinators
#include <mach7/patterns/bindings.hpp>     // Mach7 support for bindings on arbitrary UDT
#include <mach7/patterns/constructor.hpp>  // Support for constructor patterns
#include <mach7/patterns/equivalence.hpp>  // Equivalence combinator +
#include <mach7/patterns/primitive.hpp>    // Wildcard, variable and value patterns

struct Element { virtual ~Element() {} };
struct Port : Element {
  std::string name;
  Port(const char* n) : name(n) {}
};
struct Simunit : Element {
  std::string name;
  std::vector<Port*>*  ports;
  Simunit(const char* n, std::vector<Port*>*  p) : name(n), ports(p) {}
};
struct Connection : Element {
  std::string name;
  Port* port_a;
  Port* port_b;
  Connection(const char* n, Port* a, Port* b) : name(n), port_a(a), port_b(b) {}
};
struct System : Element {
  std::string name;
  std::vector<Port*>* ports;
  std::vector<Simunit*>* simunits;
  std::vector<Connection*>* connections;
  System(const char* n, std::vector<Port*>* p, std::vector<Simunit*>* s, std::vector<Connection*>* c)
    : name(n), ports(p), simunits(s), connections(c) {}
};

//------------------------------------------------------------------------------

namespace mch ///< Mach7 library namespace
{
template <> struct bindings<Port> { Members(Port::name); };
template <> struct bindings<Simunit> { Members(Simunit::name, Simunit::ports); };
template <> struct bindings<Connection> { Members(Connection::name, Connection::port_a, Connection::port_b); };
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
  var<const Element&> t1,t2;


  Match(t) {
    Case(C<Port>(str))       return os << "Port(name=" << str << ')';
    Case(C<Simunit>(str,&ps))  {
      auto ports = ps.m_value;
      os << "Simunit(name=" << str << ", ports={";
      for (auto i = ports->begin(); i != ports->end(); i++) {
        if (i != ports->begin()) os << ", ";
        os << *(*i);
      }
      return os << "})";
    }
    Case(C<Connection>(str,&pa,&pb))  {
      return os << "Connection(name=" << str <<
        ", port_a=" << pa << ", port_b=" << pb << ")";
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
  }
  EndMatch

  return os; // To prevent all control path warning
}

int main() {
  //Element* e = new Simunit("myname", new std::vector<Port*>({new Port("asdf"), new Port("fdsa")}));
  Element* e = new System("mysystem",
    new std::vector<Port*>({new Port("p1")}),
    new std::vector<Simunit*>({
      new Simunit("mysimunit", new std::vector<Port*>({
        new Port("asdf"),
        new Port("fdsa")
      }))
    }),
    new std::vector<Connection*>({
      new Connection("mycon", new Port("p1"), new Port("asdf"))
    })
  );
  std::cout << *e << std::endl;
}
