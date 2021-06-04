#ifndef _ASSET_HPP
#define _ASSET_HPP

#include <string>
#include <filesystem>

namespace Resources
{
    enum class AssetType{A_TEXTURE, A_MODEL, A_SOUND, A_ANIMATION, A_MATERIAL, A_SHADER, A_FONT};

    class Asset
    {
    protected:
        AssetType _type;
        std::string _path;

    public:

        //todo : private ?

        Asset(AssetType assetType);
        AssetType GetType() const;

        const std::string GetName() const;
        std::string& Path();
        const std::string& GetPath() const;


    };

    inline Asset::Asset(AssetType assetType) : _type{assetType}{}

    inline AssetType Asset::GetType() const
    {
        return _type;
    }

    inline const std::string Asset::GetName() const
    {
        return (std::filesystem::path(_path)).filename().string();
    }

    inline std::string &Asset::Path()
    {
        return _path;
    }
    inline const std::string& Asset::GetPath() const
    {
        return _path;
    }
}

#endif //_ASSET_HPP
