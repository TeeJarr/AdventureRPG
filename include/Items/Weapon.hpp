#include "Item.hpp"

class Weapon : public Item {
  public:
  Weapon(u_int16_t a_Damage, u_int16_t m_AttackSpeed, const char* a_ImagePath);
  void DrawIcon() const;
  u_int16_t GetDamage() const;
  u_int16_t GetAttackSpeed() const;

  private:
  u_int16_t m_Damage;
  u_int16_t m_AttackSpeed;
};
