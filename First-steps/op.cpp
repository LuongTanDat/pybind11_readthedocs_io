#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace pybind11::literals;

int add_op(int i, int j)
{
    return i + j;
}

int sub_op(int i, int j)
{
    return i - j;
}

int mul_op(int i = 1, int j = 1)
{
    return i * j;
}

double div_op(int i, int j = 1)
{
    return static_cast<double>(i) / static_cast<double>(j);
}

PYBIND11_MODULE(warp, m)
{
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add_op, "A function that adds two numbers", py::arg("i"), py::arg("j"));
    m.def("sub", &sub_op, "A function that subtracts i to j", "i"_a, "j"_a);
    m.def("mul", &mul_op, "A function that multiples 2 numbers", py::arg("i") = 1, py::arg("j") = 2);
    m.def("div", &div_op, "A function that divice 2 numbers", "i"_a, "j"_a = 1);
    m.attr("fourty_two") = 42;
    py::object hw = py::cast("hello word");
    m.attr("get_started") = hw;
}
