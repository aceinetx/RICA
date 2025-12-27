rule("rica.autoformat")
	add_deps("c++")

	on_load(function (target)
		import("lib.detect.find_tool")
		local tool = find_tool("clang-format")
		target:data_set("rica.autoformat.tool", tool)
	end)

	before_build(function (target)
		local clangformat = target:data("rica.autoformat.tool")
		if not clangformat then
			return
		end

		print("formatting code...")

		local function format(path)
			os.execv(clangformat.program, {
				"-i",
				path
			})
		end

		-- source files
		for _, file in ipairs(target:sourcefiles()) do
			if file:endswith(".cpp") then
				format(path.absolute(file))
			end
		end

		-- header files
		for _, file in ipairs(target:headerfiles()) do
			if file:endswith(".hpp") then
				format(path.absolute(file))
			end
		end

		print("code formatted")
	end)
