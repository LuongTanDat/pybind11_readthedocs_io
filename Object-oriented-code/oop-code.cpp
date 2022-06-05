#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace pybind11::literals;

struct PetStruct
{
    PetStruct(const std::string &name) : name{name} {}
    PetStruct() {}
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    void set(float w) { weight = w; }
    void set(const std::string &name_) { name = name_; }

    std::string name;
    float weight; // 1: male, 2: female
};

struct PetStruct2
{
    enum Kind
    {
        Dog = 0,
        Cat = 1
    };

    struct Attributes
    {
        float age = 0;
    };

    PetStruct2(const std::string &name, Kind type) : name(name), type(type) {}

    std::string name;
    Kind type;
    Attributes attr;
};

class PetClass
{
public:
    PetClass(const std::string &name) : name{name}, attr1{28.6}, attr2{14} {}
    void setName(const std::string &name_) { this->name = name_; }
    void setter(const float &attr1) { this->attr1 = attr1; }
    const int &getter() { return this->attr2; }
    void set(float v) { attr1 = v; }
    void set(int v) { attr2 = v; }
    const std::string &getName() const { return this->name; }

private:
    std::string name;
    float attr1;
    int attr2;
};

class Dog : PetClass
{
public:
    Dog(const std::string &name) : PetClass(name) {}
    std::string bark() const { return "woof!"; }
};

class Cat : PetClass
{
public:
    Cat(const std::string &name) : PetClass(name) {}
    std::string meow() const { return "mo^'n le'o!"; }
};

struct PolymorphicPet
{
    virtual ~PolymorphicPet() = default;
};

struct PolymorphicDog : PolymorphicPet
{
    std::string bark() const { return "woof!"; }
};

PYBIND11_MODULE(oop_warp, m)
{
    // py::class_<PetStruct>(m, "PetStruct")  // Static attribute
    py::class_<PetStruct>(m, "PetStruct", py::dynamic_attr())  // Dynamic attribute
        .def(py::init<const std::string &>(), py::arg("name"))
        .def(py::init<>())
        .def("setName", &PetStruct::setName, py::arg("name"))
        .def("getName", &PetStruct::getName)
        .def("set", py::overload_cast<float>(&PetStruct::set), py::arg("weight"), "Set the pet's weight")  // define overload functions
        .def("set", py::overload_cast<const std::string &>(&PetStruct::set), py::arg("name"), "Set the pet's name")  // define overload functions
        .def("__repr__",
             [](const PetStruct &a)
             {
                 return "<oop_warp.PetStruct named '" + a.name + "'>";
             })
        .def_readwrite("name", &PetStruct::name);  // export attribute of class

    py::class_<PetClass> pet_class(m, "PetClass");
    pet_class.def(py::init<const std::string &>())
        .def_property("name", &PetClass::getName, &PetClass::setName)
        .def("setName", &PetClass::setName, py::arg("name"))
        .def_property("attr1", nullptr, &PetClass::setter)  // define setter, getter
        .def_property("attr2", &PetClass::getter, nullptr)  // define setter, getter
        .def("set", py::overload_cast<float>(&PetClass::set), "Set the pet's attr1")  // define overload functions
        .def("set", py::overload_cast<int>(&PetClass::set), "Set the pet's attr2")    // define overload functions
        .def("__repr__",
             [](const PetClass &a)
             {
                 return "<oop_warp.PetClass named '" + a.getName() + "'>";
             });

    py::class_<Cat>(m, "Cat", pet_class)  // Inheritance
        .def(py::init<const std::string &>(), py::arg("name_cat"))
        .def("meow", &Cat::meow);

    py::class_<Dog>(m, "Dog", pet_class)   // Inheritance
        .def(py::init<const std::string &>(), py::arg("name_dog"))
        .def("bark", &Dog::bark);

    // Same binding code
    py::class_<PolymorphicPet>(m, "PolymorphicPet");
    py::class_<PolymorphicDog, PolymorphicPet>(m, "PolymorphicDog")
        .def(py::init<>())
        .def("bark", &PolymorphicDog::bark);

    // Again, return a base pointer to a derived instance
    m.def("pet_store2", []() { return std::unique_ptr<PolymorphicPet>(new PolymorphicDog); });

    // Enumerations and internal types
    py::class_<PetStruct2> pet_struct2(m, "PetStruct2");

    pet_struct2.def(py::init<const std::string &, PetStruct2::Kind>())
        .def_readwrite("name", &PetStruct2::name)
        .def_readwrite("type", &PetStruct2::type)
        .def_readwrite("attr", &PetStruct2::attr);

    py::enum_<PetStruct2::Kind>(pet_struct2, "Kind")
        .value("Dog", PetStruct2::Kind::Dog)
        .value("Cat", PetStruct2::Kind::Cat)
        .export_values();

    py::class_<PetStruct2::Attributes> attributes(pet_struct2, "Attributes");
    attributes.def(py::init<>())
        .def_readwrite("age", &PetStruct2::Attributes::age);

}
