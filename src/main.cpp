#include <pybind11/pybind11.h>
#include <iostream>
#include <pybind11/stl.h> 
#include <thread>
#include "Jieba.hpp"

// #include <Eigen/Dense>
// #include <Eigen>
using namespace std;
namespace py = pybind11;
void trainThread(int threadId){
    while(true){
        cout<<"run thread:"<<threadId<<std::endl;
    }
    
}
void start_thread(){
  std::vector<std::thread> threads;
  for (int32_t i = 0; i < 5; i++) {
    threads.push_back(std::thread([=]() { trainThread(i); }));
  }
  // Same condition as trainThread
  int i =0;
  while (i<10) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
    std::cout<<"wake"<<std::endl;
  }
  for (int32_t i = 0; i < 5; i++) {
    threads[i].join();
  }
}


PYBIND11_MODULE(jieba_pybind, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: python_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("thread_test", &start_thread, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");
    
    m.def("char_test", [](string s){
      char* c = new char(120);
      c[0]='1';
      c[1]='2';
      c[2]='3';
      c[3] = '\0';
      cout<<s.length()<<std::endl;
      return c;
    }, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");  

    py::class_<cppjieba::Jieba>(m, "cppjieba")
        .def(py::init<string,string,string,string,string>())
        .def(
            "cut",
            [](cppjieba::Jieba& m,string sentence) {
              vector<string> words;
              m.Cut(sentence,words,true);
              return words;
            });


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
