#pragma once

#include <string>

#include <sys/types.h>
enum ItemTypes { ARMOR, WEAPON, MAGIC, TREASURE, POTION, KEY_ITEM, BAUBLE };

class Item {
  public:
  u_int16_t GetPurchasePrice() const { return m_PurchaseCost; }
  u_int16_t GetSalePrice() const { return m_SaleCost; }
  u_int8_t GetItemType() const { return m_ItemType; }
  std::string GetItemName() const { return m_ItemName; }

  protected:
  u_int16_t m_PurchaseCost;
  u_int16_t m_ItemType;
  u_int16_t m_SaleCost;
  std::string m_ItemName;
};

namespace std {
  template <>
  struct hash<Item> {
    size_t operator()(const Item& key) { return hash<std::string>()(key.GetItemName()); }
  };
} // namespace std
