cmake_minimum_required(VERSION 3.31)
project(inheritencepolymorphism)

set(CMAKE_CXX_STANDARD 20)

add_executable(inheritencepolymorphism main.cpp
        Circle.cpp
        Circle.h
        Rectangle.cpp
        Rectangle.h
        ShapeFactory.cpp
        ShapeFactory.h
        Triangular.cpp
        Triangular.h)
