# Copyright (c) 2019 Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

project('light_neural_network', 'cpp', default_options : ['cpp_std=c++17'])

opencl_dep = dependency('OpenCL')
thread_dep = dependency('threads')
dep_list = [opencl_dep, thread_dep]

include_path = 'include'
src_path = 'src'
kernel_path = 'kernel'
files_script_path = 'files.py'

include_dir = include_directories(include_path, src_path)
install_subdir(include_path,
	install_dir : join_paths(get_option('includedir'), meson.project_name()),
	strip_directory : true)

src_list = run_command(files(files_script_path), src_path, '.cc')\
	.stdout().strip().split('\n')

library(meson.project_name(),
	sources : src_list,
	include_directories : include_dir,
	dependencies : dep_list,
	install : true)

install_subdir(kernel_path,
	install_dir : join_paths(get_option('datadir'), meson.project_name()))
