# Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

project('light_neural_network', 'cpp')

boost_dep = dependency('boost', modules : ['thread'])
opencl_dep = dependency('libclc')
dep_list = [boost_dep, opencl_dep]

include_path = 'include'
src_path = 'src'
kernel_path = 'kernel'
files_script_path = 'files.py'

include_dir = include_directories(include_path, src_path)
install_subdir(include_path,
	install_dir : join_paths(get_option('includedir'), meson.project_name()),
	strip_directory : true)

src_list = run_command(files(files_script_path), src_path, '.cpp')\
	.stdout().strip().split('\n')

library(meson.project_name(),
	sources : src_list,
	include_directories : include_dir,
	dependencies : dep_list,
	install : true)

install_subdir(kernel_path,
	install_dir : join_paths(get_option('datadir'), meson.project_name()))

