#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include "../ft.hpp"
#include "../containers/vector.hpp"

std::string exec(const char* cmd);

#include "vector_test.hpp"
