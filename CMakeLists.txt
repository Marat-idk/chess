cmake_minimum_required(VERSION 3.10)

project(task2 VERSION 1.0.0)

# Переменная для одиковых названий экспортруемого таргетов
set(EXPORT_TARGETS_NAME ${PROJECT_NAME}Targets)

# Определяем стандарт С++
set(CMAKE_CXX_STANDARD 17)

# Определяем суфикс для версии Debug
set(CMAKE_DEBUG_POSTFIX _g)

# Определяем флаги для компиляции файлов C (если таковые имеются)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -D_DEBUG")

# Определяем флаги для компиляции файлов C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -D_DEBUG")

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
	# Залипуха из за неправильного toolchain в автосборке
	if (CMAKE_CXX_LIBRARY_ARCHITECTURE MATCHES "^(mipsel)")
		message(STATUS "============== MIPS ===============")
	else()
		message(STATUS "============== CMAKE_CXX_FLAGS + -m32 ===============")	
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
	endif()
elseif((CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel") OR (CMAKE_CXX_LIBRARY_ARCHITECTURE MATCHES "^(mipsel)"))
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mips32r5")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mips32r5")
endif()

# Определяем список исходных файлов
file(GLOB SOURCES src/*.cpp src/*.h)

# Определяем флаги для линковки файлов для SO файлов
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ???")

# Определяем имя цели (проекта)
add_executable(${PROJECT_NAME} ${SOURCES})

# Подключаем библиотеки
# target_link_libraries(${PROJECT_NAME})

#Постфикс для Debug
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

# Задаем версию для имени файла. Используется для формирования soname.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# Настройка инсталяции.
# Опция COMPONENT нужна для команды cmake --install build --component <component_name> (доступна из cmake 3.18)
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin COMPONENT runtime)
