#include "lesson.h"

#if STRING_LESSON_ACTIVE
#include <tsg/string.h>
#include <tsg/io.h>

void lesson::run()
{
    tsg::string s("Hello World {}", 42);
    tsg::print(s);
}

#endif