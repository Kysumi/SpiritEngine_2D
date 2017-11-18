LANG = "en.lua"

function getOS()
	local raw_os_name, raw_arch_name = '', ''

	-- LuaJIT shortcut
	if jit and jit.os and jit.arch then
		raw_os_name = jit.os
		raw_arch_name = jit.arch
	else
		-- is popen supported?
		local popen_status, popen_result = pcall(io.popen, "")
		if popen_status then
			popen_result:close()
			-- Unix-based OS
			raw_os_name = io.popen('uname -s','r'):read('*l')
			raw_arch_name = io.popen('uname -m','r'):read('*l')
		else
			-- Windows
			local env_OS = os.getenv('OS')
			local env_ARCH = os.getenv('PROCESSOR_ARCHITECTURE')
			if env_OS and env_ARCH then
				raw_os_name, raw_arch_name = env_OS, env_ARCH
			end
		end
	end

	raw_os_name = (raw_os_name):lower()
	raw_arch_name = (raw_arch_name):lower()

	local os_patterns = {
		['windows'] = 'Windows',
		['linux'] = 'Linux',
		['mac'] = 'Mac',
		['darwin'] = 'Mac',
		['^mingw'] = 'Windows',
		['^cygwin'] = 'Windows',
		['bsd$'] = 'BSD',
		['SunOS'] = 'Solaris',
	}
	
	local arch_patterns = {
		['^x86$'] = 'x86',
		['i[%d]86'] = 'x86',
		['amd64'] = 'x86_64',
		['x86_64'] = 'x86_64',
		['Power Macintosh'] = 'powerpc',
		['^arm'] = 'arm',
		['^mips'] = 'mips',
	}

	local os_name, arch_name = 'unknown', 'unknown'

	for pattern, name in pairs(os_patterns) do
		if raw_os_name:match(pattern) then
			os_name = name
			break
		end
	end
	for pattern, name in pairs(arch_patterns) do
		if raw_arch_name:match(pattern) then
			arch_name = name
			break
		end
	end
	return os_name, arch_name
end



OS, Version = getOS();

function LoadFiles(folder,postfix)

	if(OS == "Windows") then
		for filename in io.popen("dir /B /A-D \""..folder.."\""):lines() do
			if filename ~= "" then
			  Tools:print(">> Loading "..postfix.." " ..filename.."\n")
			  dofile(folder .."\\".. filename)
			end
		end	
	else
		for filename in io.popen("find \""..folder.."\" -maxdepth 1 -type f "):lines() do
			if filename ~= "" then
			  Tools:print(">> Loading "..postfix.." " ..filename.."\n")
			  dofile(folder .."\\".. filename)
			end
		end	
	end
end
function LoadDirectory(folder,postfix)
	LoadFiles(folder,postfix)

	if(OS == "Windows") then
		for foldername in io.popen("dir /B /AD \""..folder.."\""):lines() do
			LoadDirectory(folder .."\\".. foldername,postfix)
		end	
	else
		for foldername in io.popen("ls -d\""..folder.."\""):lines() do
			LoadDirectory(folder .."\\".. foldername,postfix)
		end	
	end
end

LoadDirectory("Content\\Lua\\Libs","Libs")
--dofile("Content\\Lua\\Localization\\"..LANG)

function script_path()
    --printTable(debug.getinfo(3))
   local str = debug.getinfo(2, "S").source:sub(2)
   return str
end

function printTable(T,N,Buffer)
    if type(T) == 'userdata' then
        printTable(getmetatable(T),N,Buffer)
        return
    end
    
    local prevBuffer = Buffer
    if(N == nil)then
        N = "Table"
    end

    if Buffer == nil then
        Tools:print(N.." => {",false)
        Buffer = ""
    end

    Buffer = Buffer.."----------"
    for K,V in pairs(T) do
        if type(V) == 'table' then
            Tools:print(Buffer..K.." => {",false)
            Tools:printTable(V,N,Buffer)
        elseif type(V) == 'userdata' then
            Tools:print(Buffer..K.." => {",false)
            Tools:printTable(getmetatable(V),N,Buffer)
        elseif type(V) == 'function' then
            Tools:print(Buffer..K.." => "..type(V).."",false)
        elseif type(V) == 'boolean' then
            Tools:print(Buffer..K.." => "..(V and "true" or "false").."",false)
        else
            Tools:print(Buffer..K.." => "..V .."",false)
        end
    end

    if prevBuffer ~= nil then
        Tools:print(prevBuffer.."}",false)
    else
        Tools:print("}",false)
    end
end

function getFileInfo(path)

	local l = path:split("/");
	local ext = l[#l]:split(".")[2]
	local name = l[#l]:split(".")[1]
	local path = ""

	for i=1,#l-1 do
		path = path..l[i].."/"
	end

	return name, ext , path

end

function string:split(sep)
    local sep, fields = sep or ":", {}
    local pattern = string.format("([^%s]+)", sep)
    self:gsub(pattern, function(c) fields[#fields+1] = c end)
    return fields
end

function table.contains (table, val)
    for index, value in ipairs (table) do
        if value == val then
            return true
        end
    end

    return false
end

function lerp(a, b, t)
    return a * (1-t) + (b*t)
end

function lerpPosition(a, b, t)
    --(1 - t) * from + t * to
    local x = lerp(a.x, b.x, t)
    local y = lerp(a.y, b.y, t)
    return Position(x, y)
end

function Distance(a,b,c)
    if(a[1] - b[1] <= c)then
         if(a[2] - b[2] <= c)then
            return true
        end
    end
    return false
end


SCREENSTORAGE = {}
