LANG = "en.lua"
function LoadFiles(folder,postfix)
	for filename in io.popen("dir /B /A-D \""..folder.."\""):lines() do
        if filename ~= "" then
		  Tools:print(">> Loading "..postfix.." " ..filename.."\n")
		  dofile(folder .."\\".. filename)
        end
	end	
end
function LoadDirectory(folder,postfix)
	Tools:print(ffi.os)
	LoadFiles(folder,postfix)
	for foldername in io.popen("dir /B /AD \""..folder.."\""):lines() do
		LoadDirectory(folder .."\\".. foldername,postfix)
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