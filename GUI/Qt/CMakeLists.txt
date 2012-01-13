PROJECT(vtkTrackerWidget)

ADD_SUBDIRECTORY(plugin)

# CMake version requirements
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# For CMake 2.6
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

# find and setup Qt4 for this project
FIND_PACKAGE(QT4 REQUIRED)
#Qt Includes:
SET (QT_USE_QTNETWORK 1)
INCLUDE(${QT_USE_FILE})

#set( COMPILER_OPTIONS -Wall )

include_directories(
    ${AIGS_INCLUDE_DIRS}
    ${AIGS_SOURCE_DIR}/GUI/Qt
    ${AIGS_BINARY_DIR}/GUI/Qt
	${QT_INCLUDE_DIR}
    ${NDCommon_SOURCE_DIR}
    ${NDPublic_SOURCE_DIR}
)

# need an additional compiler flag for the NDLIBS
IF( WIN32 )
  ADD_DEFINITIONS( /DPLATFORM_X86CONSOLE)
ELSE( WIN32 )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive" )
  ADD_DEFINITIONS(-DPLATFORM_LINUX)
ENDIF( WIN32 )

IF(AIGS_USE_NDI)
  INCLUDE_DIRECTORIES(${VTKNDICAPI_SOURCE_DIR})
  INCLUDE_DIRECTORIES(${VTKNDICAPI_BINARY_DIR})
  SET(AuroraCal_LIBS ${AuroraCal_LIBS} vtkndicapi )
ENDIF(AIGS_USE_NDI)

link_directories( 
	${QT_LIBRARY_DIR}
)

# By default only QtCore and QtGui are enabled
#set( QT_USE_QTDESIGNER TRUE )

# widget source files.
set( WIDGET_HDR_FILES 
	vtkTrackerWidget.h
    vtkTrackerWidget_global.h
    vtkTrackerSettingsDialog.h
	vtkAuroraTrackerSettingsWidget.h
	vtkFakeTrackerSettingsWidget.h
    vtkTrackerWidgetXfrmCallback.h
    ndXfrms.h
)

set( WIDGET_SRC_FILES 
	vtkTrackerWidget.cxx
    vtkTrackerSettingsDialog.cxx
	vtkAuroraTrackerSettingsWidget.cxx
	vtkFakeTrackerSettingsWidget.cxx
    vtkTrackerWidgetXfrmCallback.cxx
    ndXfrms.cxx
)

set( WIDGET_UI_FILES
	AuroraTrackerSettingsWidget.ui
	FakeTrackerSettingsWidget.ui
    vtkTrackerSettingsDialog.ui
)

# CMake apparently doesn't do this automatically
#SET_SOURCE_FILES_PROPERTIES(vtkTrackerWidgetPlugin.cxx PROPERTIES 
#                            OBJECT_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/vtkTrackerWidget.cxx)

QT4_WRAP_CPP( GEN_WIDGET_MOC_FILES	${WIDGET_HDR_FILES})
QT4_WRAP_UI( GEN_WIDGET_UI_FILES ${WIDGET_UI_FILES})
QT4_WRAP_CPP( GEN_WIDGET_MOC_UI_FILES ${GEN_WIDGET_UI_FILES})

ADD_DEFINITIONS( -DVTKTRACKERWIDGET_LIBRARY )

add_library( vtkTrackerWidget
    ${GEN_WIDGET_MOC_UI_FILES}
	${GEN_WIDGET_MOC_FILES}
    ${WIDGET_HDR_FILES}
	${WIDGET_SRC_FILES}
    )
       
target_link_libraries( vtkTrackerWidget
    ${QT_LIBRARIES}
    vtkTracking 
    vtkndicapi )    

install( TARGETS vtkTrackerWidget DESTINATION bin )

# install the executable.
INSTALL(TARGETS vtkTrackerWidget 
        RUNTIME DESTINATION bin 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib/static 
        COMPONENT AIGS )