# Указываем правила установки библиотеки
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} boost_serialization
  boost_array
  boost_assert
  boost_concept_check
  boost_config
  boost_container_hash
  boost_core
  boost_detail
  boost_endian
  boost_function
  boost_function_types
  boost_fusion
  boost_integer
  boost_io
  boost_iterator
  boost_move
  boost_mp11
  boost_mpl
  boost_optional
  boost_phoenix
  boost_pool
  boost_predef
  boost_preprocessor
  boost_proto
  boost_range
  boost_smart_ptr
  boost_spirit
  boost_static_assert
  boost_thread
  boost_throw_exception
  boost_type_index
  boost_type_traits
  boost_typeof
  boost_unordered
  boost_utility
  boost_variant
  boost_atomic
  boost_bind
  boost_chrono
  boost_container
  boost_conversion
  boost_date_time
  boost_describe
  boost_exception
  boost_functional
  boost_regex
  boost_system
  boost_tuple
  boost_winapi
  boost_ratio
  boost_intrusive
  boost_algorithm
  boost_lexical_cast
  boost_numeric_conversion
  boost_tokenizer
  boost_variant2
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # Установка библиотеки
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # Установка исполняемых файлов (если есть)
)

# Устанавливаем заголовочные файлы
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}) # Копируем заголовочные файлы в системную директорию include

# Экспортируем целевой объект для использования в других проектах
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
