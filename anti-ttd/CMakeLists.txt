set(anti-ttd_STATIC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(anti-ttd_STATIC_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# anti-ttd sources
set(anti-ttd_SRC
	${anti-ttd_STATIC_SRC}/DebugFilterState.cpp
	${anti-ttd_STATIC_SRC}/Handles.cpp
	${anti-ttd_STATIC_SRC}/PageGuard.cpp
	${anti-ttd_STATIC_SRC}/ParentProcessName.cpp
	${anti-ttd_STATIC_SRC}/anti-ttd.cpp
)

set(anti-ttd_INCLUDE
	${anti-ttd_STATIC_INCLUDE}/DebugFilterState.h
	${anti-ttd_STATIC_INCLUDE}/Handles.h
	${anti-ttd_STATIC_INCLUDE}/PageGuard.h
	${anti-ttd_STATIC_INCLUDE}/ParentProcessName.h
)

add_executable(anti-ttd ${anti-ttd_SRC} ${anti-ttd_INCLUDE})
target_include_directories(anti-ttd PUBLIC ${anti-ttd_STATIC_INCLUDE})

if(MSVC)
	add_definitions(-DWIN32 -DUNICODE -D_UNICODE)
	target_compile_options(anti-ttd PUBLIC "$<$<CONFIG:DEBUG>:/MTd>" "$<$<CONFIG:DEBUG>:/WX>")
	target_compile_options(anti-ttd PUBLIC "$<$<CONFIG:RELEASE>:/MT>" "$<$<CONFIG:RELEASE>:/WX>")
endif()
