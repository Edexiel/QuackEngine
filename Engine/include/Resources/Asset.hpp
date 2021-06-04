#ifndef _ASSET_HPP
#define _ASSET_HPP

#include <string>
#include <filesystem>

namespace Resources
{
    enum class AssetType{A_TEXTURE, A_MODEL, A_SOUND, A_ANIMATION, A_MATERIAL, A_SHADER};

    class Asset
    {
    protected:
        AssetType _type;
        std::filesystem::path _path;

    public:

        explicit Asset(AssetType assetType);

        AssetType GetType() const;
        std::string GetName() const;
        std::string GetPath()const;
        void SetPath(const std::string& path);
        void SetPath(const std::filesystem::path& path);

    };

    inline Asset::Asset(AssetType assetType) : _type{assetType}{}

    inline AssetType Asset::GetType() const
    {
        return _type;
    }

    inline std::string Asset::GetName() const
    {
        return _path.filename().string();
    }

    inline std::string Asset::GetPath() const
    {

        return _path.generic_string();
    }
    inline void Asset::SetPath(const std::string& path)
    {
        _path = std::filesystem::path{path};
    }
    inline void Asset::SetPath(const std::filesystem::path& path)
    {
        _path = path;
    }
}

#endif //_ASSET_HPP
