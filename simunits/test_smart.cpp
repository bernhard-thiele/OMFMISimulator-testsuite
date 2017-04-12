#include <memory>
#include <iostream>

struct myclass {
  std::string name;
  int number;
};

struct keep {
  keep(std::shared_ptr<myclass> aa) : a(aa) {};
  void miua() {
    std::cout << "miua: " << a->name << a->number << std::endl;
  }
  std::shared_ptr<myclass> a;
};

struct keep2 {
  keep2(const std::shared_ptr<myclass>& aa) : a(aa) {};
  void miua2() {
    std::cout << "miua2: " << a->name << a->number << std::endl;
  }
  std::shared_ptr<myclass> a;
};

struct keep3 {
  keep3(std::unique_ptr<myclass>& aa) : a(std::move(aa)) {};
  void miua3() {
    std::cout << "miua3: " << a->name << a->number << std::endl;
  }
  std::unique_ptr<myclass> a;
};

struct keep4 {
  keep4(std::unique_ptr<myclass> aa) : a(std::move(aa)) {};
  void miua4() {
    std::cout << "miua4: " << a->name << a->number << std::endl;
  }
  std::unique_ptr<myclass> a;
};

void bark1(std::shared_ptr<myclass> a) {
  std::cout << "bark: " << a->name << a->number << std::endl;
}

void bark2(const std::shared_ptr<myclass>& a) {
  std::cout << "bark: " << a->name << a->number << std::endl;
}

int main() {
  std::cout << "Hello there\n";

  std::shared_ptr<myclass> t1(new myclass{"asdf", 32});

  t1->name = "Hello";

  std::cout << t1->name << t1->number << std::endl;

  std::shared_ptr<myclass> t2 = t1;
  t2->name = "changed";
  std::cout << t1->name << t2->number << std::endl;

  bark1(t1); bark2(t1);
  keep k(t1);
  k.miua();

  std::shared_ptr<myclass> t3(std::make_shared<myclass>());
  t3->name = "whatsthis"; t3->number = 2;
  keep2 k2(t3);
  k2.miua2();
  t3.reset();
  k2.miua2();
  keep2 k2b(std::make_shared<myclass>());
  k2b.a->name = "ahola"; k2b.a->number = 111;
  k2b.miua2();
  keep2 k2c(std::shared_ptr<myclass>(new myclass{"uups", 24}));
  k2c.miua2();



  std::unique_ptr<myclass> u1(new myclass{"fdsa", 22});
  std::cout << u1->name << u1->number << std::endl;

  std::unique_ptr<myclass> u2 = std::move(u1);
  std::cout << u2->name << u2->number << std::endl;
  // std::cout << u1->name << u1->number << std::endl; // error
  keep3 k3(u2);
  k3.miua3();
  // std::cout << u2->name << u2->number << std::endl; // segmentation fault
  keep4 k4(std::unique_ptr<myclass>(new myclass{"wohaa", 21}));
  k4.miua4();

  // std::unique_ptr<myclass> u3(new myclass{"faaas", 20}); keep4 k4b(u3); // Not working!?

  return 0;
}
