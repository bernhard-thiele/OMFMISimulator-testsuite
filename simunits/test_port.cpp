#include <iostream>
#include <string>

// Trying to get inspiration from
// http://support.objecteering.com/objecteering6.1/help/us/cxx_developer/tour/generating_parts_and_ports.htm
// 2017-04-16: Strange ...

struct IScalarInputReal {
  virtual ~IScalarInputReal() {};
  virtual std::string kind() const = 0;
  virtual void set(double value) = 0;
};
struct IScalarOutputReal {
  virtual ~IScalarOutputReal() {};
  virtual std::string kind() const = 0;
  virtual double get() const = 0;
};

struct ScalarOutputReal;
struct ScalarInputReal : public IScalarInputReal{
  std::string kind() const override {return "ScalarInputReal";}
  void set(double value) override { value_=value; std::cout << "set(" << value << ")\n"; }
private:
  friend ScalarOutputReal;
  double value_; // alternative: Go through "parent", e.g., parent->value_ = value
};
struct ScalarOutputReal : public IScalarOutputReal{
  ScalarOutputReal(ScalarInputReal* sir) : sir_(sir) {}
  std::string kind() const override {return "ScalarOutputReal";}
  double get() const override { std::cout << "get(x)\n"; return sir_->value_; }
private:
  ScalarInputReal* sir_; // alternative: Go through "parent", e.g., return parent->value_
};

struct CompositeScalarInputRealPort {
  CompositeScalarInputRealPort() {
    sirport = new ScalarInputReal();
    sorport = new ScalarOutputReal(sirport);
  }
  IScalarInputReal* getProvidedIScalarInputReal() {return sirport;}
  IScalarOutputReal* getRequiredIScalarOutputReal() {return sorport;}
private:
  ScalarInputReal* sirport;
  ScalarOutputReal* sorport;
};

struct Composite {
  CompositeScalarInputRealPort* getScalarInputRealPort() {return &sirport;}

  void simulate();

private:
  CompositeScalarInputRealPort sirport; // possibly created as smart pointer via dependency injection ...
};

inline void Composite::simulate() {
  // Retrieving the port
  CompositeScalarInputRealPort* scalarInputRealPort = getScalarInputRealPort();
  // getting the required plug
  IScalarOutputReal* scalarOutputReal = scalarInputRealPort->getRequiredIScalarOutputReal();
  double in = scalarOutputReal->get();
  std::cout << "simulate() got: " << in << std::endl;
}

int main() {
  std::cout << "hello world\n";
  Composite composite;
  // Retrieving the port
  CompositeScalarInputRealPort* scalarInputRealPort = composite.getScalarInputRealPort();
  // getting the provided plug
  IScalarInputReal* scalarInputReal = scalarInputRealPort->getProvidedIScalarInputReal();
  scalarInputReal->set(22);

  composite.simulate();
}
