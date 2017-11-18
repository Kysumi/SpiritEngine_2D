
local Lookup = 
				{
					{
						Type = "Texture",
						Ext = {"png","jpg","bmp","jpeg"},
						Func = nil,
					},
					{
						Type = "Font",
						Ext = {"otf"},
						Func = nil,
					},
					{
						Type = "Sound",
						Ext = {"mp3","wav","ogg"},
						Func = nil,
					},
				
			}

function LoadAsset (asset)

	--Tools:print(asset);
	local name, ext, path = getFileInfo(asset)
	--Tools:print(ext)
	--Tools:print(path)

	local data = nil

	for key, value in ipairs(Lookup) do
		if table.contains(value.Ext,ext) then
			data = value
		end
	end

	--Tools:print(data.Type)
	data.Func(name, asset)

end

function IsAssetLoaded (asset)

	local name, ext, path = getFileInfo(asset)

	for _,table in ipairs(Content:getLoaded()) do
		Tools:print("Matching: "..table.Name.." => "..name)
		if(table.Name == name) then
			return true
		end
	end
	
	return false
end

function LoadTexture(name ,asset)

	--CALL C++ HOOK FOR LOADING TEXTURE
	Content:loadTexture(name, asset)
end

function LoadFont(name ,asset)

	--CALL C++ HOOK FOR LOADING FONT
	Content:loadFont(name, asset)

end

function LoadSound(name ,asset)

	--CALL C++ HOOK FOR LOADING SOUND
	Content:loadSound(name, asset)

end

Lookup[1].Func = LoadTexture
Lookup[2].Func = LoadFont
Lookup[3].Func = LoadSound
