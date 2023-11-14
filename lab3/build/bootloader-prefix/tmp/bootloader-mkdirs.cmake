# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP_IDF/Espressif/frameworks/esp-idf-v5.1.1/components/bootloader/subproject"
  "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader"
  "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix"
  "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix/tmp"
  "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix/src"
  "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/NHAN/OneDrive/Desktop/lab_embedded/lab3/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
