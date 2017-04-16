#include <iostream>
#include <string>

// Trying to get inspiration from
// http://www.jot.fm/issues/issue_2004_11/column5/
// Musing about it: The article above doesn't really say how to implement the concrete port in practice, particularly the "use" association. The "implement" relation would straight-forwardly translate to inheriting from the interace as implemented below. This is still all strange. Possible to combine this with the "D3.3" report approach, Listing 1, where we have the FMU1 structure which provides "buffering" and caching facilities?

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
struct Composite;
struct ScalarInputReal : public IScalarInputReal{
  std::string kind() const override {return "ScalarInputReal";}
  void set(double value) override; // Need full Composite type known to compiler, so function is defined somewhere below.

  void setParent(Composite* parent) {parent_=parent;}

  // "using" IScalarOutputReal
  // double get() const {return sor_->get();} // variant 1: Delegation of methods
  IScalarOutputReal* getRequiredIScalarOutputReal() {return sor_;} // variant 2: Get interface
  // IScalarOutputReal* getInsideIScalarOutputReal() {return sor_;} // Different naming. Inside vs Outside
  void setRequiredScalarOutputReal(IScalarOutputReal* sor) {sor_ = sor;}
private:
  IScalarOutputReal* sor_;
  Composite* parent_;
};
struct ScalarOutputReal : public IScalarOutputReal{
  ScalarOutputReal(ScalarInputReal* sir) : sir_(sir) {}
  std::string kind() const override {return "ScalarOutputReal";}
  double get() const override { std::cout << "ScalarOutputReal.get() source providing constant value '23'.\n"; return 23; }
  /* Instead of "delegating" to the real source component, the port could access the (cached) private member variable of the Composite "parent", hence the variable set by ScalarInputReal.set(x) */
private:
  ScalarInputReal* sir_;
};

struct Composite {
  Composite() {sirport_.setParent(this);}
  void simulate();

  IScalarInputReal* getProvidedIScalarInputReal() {return &sirport_;}
  void setRequiredScalarOutputReal(IScalarOutputReal* sor) {
    sirport_.setRequiredScalarOutputReal(sor);
  }

  void setScalarRealValue(double value) {scalarRealValue_=value;}
private:
  ScalarInputReal sirport_;
  double scalarRealValue_;
};

inline void ScalarInputReal::set(double value) { std::cout << "ScalarInputReal.set(" << value << ")\n"; parent_->setScalarRealValue(value); }

inline void Composite::simulate() {
  IScalarOutputReal* sor = sirport_.getRequiredIScalarOutputReal();
  std::cout << "simulate(); Accessing the connected outside output port to *provide/get* *required* value for input port: " << sor->get() << std::endl;
  std::cout << "simulate(); Accessing private member variable that was set from outside using provided input port setter method: " << scalarRealValue_ << std::endl;
}

int main() {
  std::cout << "hello world\n";
  Composite composite;
  ScalarOutputReal source(nullptr);
  composite.setRequiredScalarOutputReal(&source);

  // Retrieving the provided port
  IScalarInputReal* scalarInputReal = composite.getProvidedIScalarInputReal();
  scalarInputReal->set(22);

  composite.simulate();
}
