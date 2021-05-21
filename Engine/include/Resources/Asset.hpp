#ifndef _ASSET_HPP
#define _ASSET_HPP

#include <string>

namespace Resources
{
    enum class ASSET_TYPE{A_TEXTURE, A_MODEL, A_SOUND, A_ANIMATION, A_MATERIAL};

    class Asset
    {
    protected:
        ASSET_TYPE _type;

    public:

        std::string name;
        //todo : private

        Asset(ASSET_TYPE assetType);
        ASSET_TYPE GetType() const;
        const std::string &GetPath() const;

    };

    inline Asset::Asset(ASSET_TYPE assetType) : _type{assetType}{}

    inline ASSET_TYPE Asset::GetType() const
    {
        return _type;
    }

    inline const std::string &Asset::GetPath() const
    {
        return name;
    }
}

#endif //_ASSET_HPP
