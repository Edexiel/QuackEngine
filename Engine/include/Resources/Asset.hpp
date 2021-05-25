#ifndef _ASSET_HPP
#define _ASSET_HPP

#include <string>

namespace Resources
{
    enum class AssetType{A_TEXTURE, A_MODEL, A_SOUND, A_ANIMATION, A_MATERIAL, A_SHADER};

    class Asset
    {
    protected:
        AssetType _type;

    public:

        std::string name;
        //todo : private ?

        Asset(AssetType assetType);
        AssetType GetType() const;
    };

    inline Asset::Asset(AssetType assetType) : _type{assetType}{}

    inline AssetType Asset::GetType() const
    {
        return _type;
    }
}

#endif //_ASSET_HPP
