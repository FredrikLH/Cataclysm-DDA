#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "item.h"
#include <string>
#include <vector>
#include <list>

class game;
class map;

const extern std::string inv_chars;

typedef std::list< std::list<item> > invstack;
typedef std::vector< std::list<item>* > invslice;

class inventory
{
 public:
  item& operator[] (int i);
  invslice slice(int start, int length);
  invslice slice(const std::list<item>* stack, int length);
  std::list<item>& stack_by_letter(char ch);
  std::list<item> const_stack(int i) const;
  int size() const;
  int num_items() const;
  bool is_sorted() const;

  inventory& operator=  (inventory &rhs);
  inventory& operator=  (const inventory &rhs);
  inventory& operator+= (const inventory &rhs);
  inventory& operator+= (const item &rhs);
  inventory& operator+= (const std::list<item> &rhs);
  inventory  operator+  (const inventory &rhs);
  inventory  operator+  (const item &rhs);
  inventory  operator+  (const std::list<item> &rhs);

  void unsort(); // flags the inventory as unsorted
  void sort();
  void clear();
  void add_stack(std::list<item> newits);
  void push_back(std::list<item> newits);
  void add_item (item newit, bool keep_invlet = false);
  void add_item_keep_invlet(item newit);
  void push_back(item newit);

/* Check all items for proper stacking, rearranging as needed
 * game pointer is not necessary, but if supplied, will ensure no overlap with
 * the player's worn items / weapon
 */
  void restack(player *p = NULL);

  void form_from_map(game *g, point origin, int distance);

  std::list<item> remove_stack_by_letter(char ch);
  std::list<item> remove_partial_stack(char ch, int amount);
  item  remove_item(item *it);
  item  remove_item_by_type(itype_id type);
  item  remove_item_by_letter(char ch);
  item  remove_item_by_letter_and_quantity(char ch, int quantity); // charged items, not stacks
  std::vector<item>  remove_mission_items(int mission_id);
  item& item_by_letter(char ch);
  int   index_by_letter(char ch);

// Below, "amount" refers to quantity
//        "charges" refers to charges
  int  amount_of (itype_id it);
  int  charges_of(itype_id it);

  void use_amount (itype_id it, int quantity, bool use_container = false);
  void use_charges(itype_id it, int quantity);

  bool has_amount (itype_id it, int quantity);
  bool has_charges(itype_id it, int quantity);
  bool has_item(item *it); // Looks for a specific item

  bool has_mission_item(int mission_id) const;
  int butcher_factor() const;
  bool has_artifact_with(art_effect_passive effect) const;

  int weight() const;
  int volume() const;
  int max_active_item_charges(itype_id id) const;

  void dump(std::vector<item>& dest); // dumps contents into dest (does not delete contents)

  // vector rather than list because it's NOT an item stack
  std::vector<item*> active_items();

  // hack to account for players saving inventory data (including weapon, etc.)
  std::string save_str_no_quant() const;

/* TODO: This stuff, I guess?
  std::string save();
  void load(std::string data);
*/

  item nullitem;
  std::list<item> nullstack;
 private:
  item remove_item(invstack::iterator iter);
  void assign_empty_invlet(item &it, player *p = NULL);
  invstack items;
  bool sorted;
};

#endif
