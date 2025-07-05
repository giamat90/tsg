#include "lesson.h"

#if LOGGER_LESSON_ACTIVE

#include <tsg/logger.h>

void lesson::run()
{
    tsg::logger::get_istance("log42.txt", true);
    tsg::logger::get_istance().write("Hello World");
    tsg::logger::get_istance().write("Hello Eath {}", 616);

}

#endif