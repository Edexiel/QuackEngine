#ifndef _ASSET_HPP
#define _ASSET_HPP

namespace Resources
{
    enum class ASSET_TYPE{A_TEXTURE, A_MODEL, A_SOUND, A_ANIMATION, A_MATERIAL};

    class Asset
    {
    protected:
        ASSET_TYPE _type;

    public:
        Asset(ASSET_TYPE assetType);
        ASSET_TYPE GetType() const;
    };

    inline Asset::Asset(ASSET_TYPE assetType) : _type{assetType}{}

    inline ASSET_TYPE Asset::GetType() const
    {
        return _type;
    }
}

#endif //_ASSET_HPP
