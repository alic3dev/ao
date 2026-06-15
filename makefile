name=ao

directory_cer0=../cer0
directory_cer0_include=${directory_cer0}/include
directory_cer0_library=${directory_cer0}/library/macos/release

directory_cexil=../cexil
directory_cexil_include=${directory_cexil}/include
directory_cexil_library=${directory_cexil}/library/macos/release

directory_clic3=../clic3
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library/macos/release

directory_interrupt_handler=../interrupt_handler
directory_interrupt_handler_include=${directory_interrupt_handler}/include
directory_interrupt_handler_library=${directory_interrupt_handler}/library/macos/release

directory_math_c=../math_c
directory_math_c_include=${directory_math_c}/include
directory_math_c_library=${directory_math_c}/library/macos/release

directory_include=include
directory_objects=objects
directory_output=output
directory_sources=sources

file_library_cer0=${directory_cer0_library}/cer0.dylib
file_library_cexil=${directory_cexil_library}/cexil.o
file_library_clic3=${directory_clic3_library}/clic3.dylib
file_library_interrupt_handler=${directory_interrupt_handler_library}/interrupt_handler.dylib

file_output=${directory_output}/${name}

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

ifndef target_device_version
	target_device_version=26.1
endif

target_platform=arm64-apple-macos${target_device_version}

directory_sdk=${shell xcrun --sdk macosx${target_device_version} --show-sdk-path}

cc=clang
c_flags_platform=-target ${target_platform} -isysroot ${directory_sdk}
c_flags=-O3 ${c_flags_platform} -I${directory_include} -I${directory_cer0_include} -I${directory_cexil_include} -I${directory_clic3_include} -I${directory_interrupt_handler_include} -I${directory_math_c_include}
c_flags_executable=-framework CoreAudio

strip=strip
strip_flags=

${file_output}: ${files_objects}
	mkdir -p ${directory_output}
	${cc} ${c_flags} ${c_flags_executable} ${files_objects} ${file_library_cer0} ${file_library_cexil} ${file_library_clic3} ${file_library_interrupt_handler} -o ${file_output}
	${strip} ${strip_flags} ${file_output}

${directory_objects}/%.o: ${directory_sources}/%.c
	mkdir -p ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

clean: clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects} 2> /dev/null

clean_output:
	-rm -r ${directory_output} 2> /dev/null
