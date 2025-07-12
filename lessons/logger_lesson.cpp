#include "lesson.h"

#if LOGGER_LESSON_ACTIVE

#include <tsg/logger.h>

void lesson::run()
{
    tsg::logger::get_instance("log42.txt", true);
    tsg::logger::get_instance().write("Hello World");
    tsg::logger::get_instance().write("Hello Eath {}", 616);

}

#endif