# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers sources, headers, ou changer
# des flags de compilation.
champion-srcs = prologin.cc utils.cpp actions.cpp loopavoider.cpp
champion-dists = utils.h actions.h loopavoider.h
champion-cxxflags = -ggdb3 -Wall -std=c++11

# Evite de toucher a ce qui suit
champion-dists += prologin.hh
STECHEC_LANG=cxx
include ../includes/rules.mk
