# Install script for directory: C:/Users/musi/Downloads/cegui-0.8.7/samples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/cegui")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cegui-0/samples" TYPE FILE FILES "C:/Users/musi/Desktop/39.105.4.19/CEGUI2/datafiles/samples/samples.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/HelloWorld/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/LookNFeelOverview/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/GameMenu/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/HUDDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/DragDropDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/InventoryDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/EffectsDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/FontDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/Demo6/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/EditboxValidationDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/Minesweeper/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/ScrollablePaneDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/TabControlDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/CommonDialogsDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/WidgetDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/TextDemo/cmake_install.cmake")
  include("C:/Users/musi/Desktop/39.105.4.19/CEGUI2/samples/TreeDemo/cmake_install.cmake")

endif()

