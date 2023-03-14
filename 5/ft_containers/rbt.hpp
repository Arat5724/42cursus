#ifndef RBT_HPP
#define RBT_HPP

#include <functional>
#include <iostream>

#include "iterator.hpp"
#include "pair.hpp"
#include "type_traits.hpp"
#include "utils.hpp"

#define RED 0
#define BLACK 1

template <typename T__>
struct rbtree_node {
  T__* value;
  rbtree_node* right;
  rbtree_node* left;
  rbtree_node* parent;
  char color;
};

template <typename T_, typename Pointer_, typename Reference_>
class rbtree_iterator {
 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef T_ value_type;
  typedef Pointer_ pointer;
  typedef Reference_ reference;

  typedef rbtree_iterator<T_, T_*, T_&> iterator;
  typedef rbtree_node<value_type> node;

 private:
  node* n;

  node* get_next_node(node* curr) {
    if (curr->right->value) {
      curr = curr->right;
      while (curr->parent->value && curr->left->value) curr = curr->left;
      return curr;
    }
    while (curr->parent->value && curr != curr->parent->left)
      curr = curr->parent;
    return curr->parent;
  }

  node* get_prev_node(node* curr) {
    if (curr->left->value) {
      curr = curr->left;
      while (curr->right->value) curr = curr->right;
      return curr;
    }
    while (curr->parent->value && curr != curr->parent->right)
      curr = curr->parent;
    return curr->parent;
  }

 public:
  rbtree_iterator() : n(NULL){};
  explicit rbtree_iterator(node* const node) : n(node) {}
  rbtree_iterator(const iterator& other) : n(other.get_node()) {}

  rbtree_iterator& operator=(const iterator& other) {
    this->n = other.get_node();
    return *this;
  }

  reference operator*() const { return *(this->n->value); }
  pointer operator->() const { return this->n->value; }

  rbtree_iterator& operator++() {
    this->n = get_next_node(this->n);
    return *this;
  }
  rbtree_iterator operator++(int) {
    node* temp = this->n;
    this->n = get_next_node(this->n);
    return rbtree_iterator(temp);
  }

  rbtree_iterator& operator--() {
    this->n = get_prev_node(this->n);
    return *this;
  }
  rbtree_iterator operator--(int) {
    node* temp = this->n;
    this->n = get_prev_node(this->n);
    return rbtree_iterator(temp);
  }

  friend bool operator==(const rbtree_iterator& it1,
                         const rbtree_iterator& it2) {
    return it1.n == it2.n;
  }

  friend bool operator!=(const rbtree_iterator& it1,
                         const rbtree_iterator& it2) {
    return !(it1 == it2);
  }

  node* get_node() { return n; }
  node* get_node() const { return n; }
};

template <typename Key, typename Value, typename ExtractKey,
          typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Value> >
class rbtree {
 private:
 public:
  typedef Key key_type;
  typedef Value value_type;
  typedef Allocator allocator_type;

  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  typedef rbtree_iterator<value_type, pointer, reference> iterator;
  typedef rbtree_iterator<value_type, const_pointer, const_reference>
      const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  typedef Compare key_compare;
  typedef rbtree_node<value_type> node;

  typedef ExtractKey extract;
  typedef
      typename allocator_type::template rebind<node>::other node_allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;

 private:
  allocator_type value_allocator_;
  node_allocator_type node_allocator_;
  extract extractor_;
  key_compare comparator_;
  node* nil_;
  node* root_;
  node* anchor_;
  size_type size_;

 public:
  rbtree()
      : value_allocator_(allocator_type()),
        node_allocator_(node_allocator_type()),
        extractor_(extract()),
        comparator_(key_compare()),
        nil_(init_nil()),
        root_(this->nil_),
        anchor_(init_nil()),
        size_(0) {}

  explicit rbtree(const key_compare& comp,
                  const allocator_type& alloc = allocator_type())
      : value_allocator_(alloc),
        node_allocator_(node_allocator_type()),
        extractor_(extract()),
        comparator_(comp),
        nil_(init_nil()),
        root_(this->nil_),
        anchor_(init_nil()),
        size_(0) {}

  template <typename InputIt>
  rbtree(InputIt first, InputIt last, const Compare& comp = Compare(),
         const allocator_type& alloc = allocator_type())
      : value_allocator_(alloc),
        node_allocator_(node_allocator_type()),
        extractor_(extract()),
        comparator_(comp),
        nil_(init_nil()),
        root_(this->nil_),
        anchor_(init_nil()),
        size_(0) {
    insert(first, last);
  }

  rbtree(const rbtree& other)
      : value_allocator_(other.value_allocator_),
        node_allocator_(other.node_allocator_),
        extractor_(other.extractor_),
        comparator_(other.comparator_),
        nil_(init_nil()),
        root_(this->nil_),
        anchor_(init_nil()),
        size_(0) {
    for (const_iterator it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
  }

  ~rbtree() {
    if (this->root_->value) clear_all_node(this->root_);

    delete this->nil_;
    delete this->anchor_;
  }

  rbtree& operator=(const rbtree& other) {
    rbtree temp(other);
    this->swap(temp);
    return *this;
  }

  allocator_type get_allocator() const throw() {
    return this->value_allocator_;
  }

  iterator begin() throw() {
    if (this->size()) {
      return iterator(this->anchor_->right);
    }
    return iterator(this->anchor_);
  }
  const_iterator begin() const throw() {
    if (this->size()) {
      return const_iterator(this->anchor_->right);
    }
    return const_iterator(this->anchor_);
  }

  iterator end() throw() { return iterator(this->anchor_); }
  const_iterator end() const throw() { return const_iterator(this->anchor_); }

  reverse_iterator rbegin() throw() {
    return reverse_iterator(iterator(this->anchor_));
  }
  const_reverse_iterator rbegin() const throw() {
    return const_reverse_iterator(const_iterator(this->anchor_));
  }

  reverse_iterator rend() throw() {
    if (this->size()) {
      return reverse_iterator(iterator(this->anchor_->right));
    }
    return reverse_iterator(iterator(this->anchor_));
  }
  const_reverse_iterator rend() const throw() {
    if (this->size()) {
      return const_reverse_iterator(const_iterator(this->anchor_->right));
    }
    return const_reverse_iterator(const_iterator(this->anchor_));
  }

  bool empty() const throw() { return this->size_ == 0; }

  size_type size() const throw() { return this->size_; }

  size_type max_size() const throw() {
    return std::numeric_limits<difference_type>::max(),
           std::numeric_limits<size_type>::max() /
               (sizeof(node) + sizeof(value_type));
  }

  void clear() throw() {
    this->clear_all_node(this->root_);
    this->size_ = 0;
    this->anchor_->parent = NULL;
    this->anchor_->left = this->anchor_;
    this->anchor_->right = this->anchor_;
    this->root_ = this->nil_;
  }

  ft::pair<iterator, bool> insert(const_reference value) {
    if (!this->size_) {
      insert_root(value);
      return ft::make_pair(iterator(this->root_), true);
    }
    node* parent = this->root_;
    node* new_node = init_node(value);
    node* temp;
    while (parent->value) {
      temp = parent;
      if (compare(new_node, parent))
        parent = parent->left;
      else if (compare(parent, new_node))
        parent = parent->right;
      else {
        this->destroy_node(new_node);
        return ft::make_pair(iterator(parent), false);
      }
    }

    new_node->parent = temp;
    if (compare(new_node, temp))
      temp->left = new_node;
    else
      temp->right = new_node;

    insert_fixup(new_node);

    this->size_ += 1;
    update_anchor();

    return ft::make_pair(iterator(new_node), true);
  }

  iterator insert(iterator hint, const_reference value) {
    if (!this->size_) {
      insert_root(value);
      return iterator(this->root_);
    }

    node* parent = hint.get_node();
    if (parent == this->anchor_) parent = parent->right;
    node* new_node = init_node(value);
    if (compare(new_node, parent))
      while (parent->parent->value && compare(new_node, parent))
        parent = parent->parent;
    else if (compare(parent, new_node))
      while (parent->parent->value && compare(parent, new_node))
        parent = parent->parent;
    if (!(compare(new_node, parent) || compare(parent, new_node))) {
      destroy_node(new_node);
      return iterator(parent);
    }

    node* temp = NULL;
    while (parent->value) {
      temp = parent;
      if (compare(new_node, parent))
        parent = parent->left;
      else if (compare(parent, new_node))
        parent = parent->right;
      else
        return iterator(parent);
    }

    new_node->parent = temp;
    if (compare(new_node, temp))
      temp->left = new_node;
    else
      temp->right = new_node;

    insert_fixup(new_node);

    this->size_ += 1;
    update_anchor();

    return iterator(new_node);
  }

  const_iterator insert(const_iterator hint, const_reference value) {
    if (!this->size_) {
      insert_root(value);
      return iterator(this->root_);
    }

    node* parent = hint.get_node();
    if (parent == this->anchor_) parent = parent->right;
    node* new_node = init_node(value);
    if (compare(new_node, parent))
      while (parent->parent->value && compare(new_node, parent))
        parent = parent->parent;
    else if (compare(parent, new_node))
      while (parent->parent->value && compare(parent, new_node))
        parent = parent->parent;
    if (!(compare(new_node, parent) || compare(parent, new_node))) {
      destroy_node(new_node);
      return iterator(parent);
    }

    node* temp = NULL;
    while (parent->value) {
      temp = parent;
      if (compare(new_node, parent))
        parent = parent->left;
      else if (compare(parent, new_node))
        parent = parent->right;
      else
        return iterator(parent);
    }

    new_node->parent = temp;
    if (compare(new_node, temp))
      temp->left = new_node;
    else
      temp->right = new_node;

    insert_fixup(new_node);

    this->size_ += 1;
    update_anchor();

    return iterator(new_node);
  }

  template <typename InputIt>
  void insert(
      InputIt first,
      typename ft::enable_if<ft::is_input_iterator<typename ft::iterator_traits<
                                 InputIt>::iterator_category>::value,
                             InputIt>::type last) {
    for (; first != last; ++first) insert(*first);
  }

  void erase(iterator pos) {
    node* pos_node = pos.get_node();
    node* new_parent;
    char original_color = pos_node->color;

    iterator new_begin = ++(this->begin());
    iterator new_end = --(--(this->end()));

    if (!pos_node->left->value) {
      new_parent = pos_node->right;
      this->transplant_node(pos_node, pos_node->right);
    } else if (!pos_node->right->value) {
      new_parent = pos_node->left;
      this->transplant_node(pos_node, pos_node->left);
    } else {
      node* replace = (--pos).get_node();
      original_color = replace->color;
      new_parent = replace->left;
      if (replace->parent != pos_node) {
        this->transplant_node(replace, replace->left);
        replace->left = pos_node->left;
        replace->left->parent = replace;
      } else {
        new_parent->parent = replace;
      }
      this->transplant_node(pos_node, replace);
      replace->right = pos_node->right;
      replace->right->parent = replace;
      replace->color = pos_node->color;
    }

    if (original_color == BLACK) this->delete_fixup(new_parent);

    if (pos_node == this->anchor_->right) {
      this->anchor_->right = new_begin.get_node();
      new_begin.get_node()->left = this->anchor_;
    }

    if (pos_node == this->anchor_->left) {
      this->anchor_->left = new_end.get_node();
      new_end.get_node()->right = this->anchor_;
    }
    this->size_ -= 1;
    this->destroy_node(pos_node);
  }

  void erase(const_iterator pos) {
    node* pos_node = pos.get_node();
    node* new_parent;
    char original_color = pos_node->color;

    iterator new_begin = ++(this->begin());
    iterator new_end = --(--(this->end()));

    if (!pos_node->left->value) {
      new_parent = pos_node->right;
      this->transplant_node(pos_node, pos_node->right);
    } else if (!pos_node->right->value) {
      new_parent = pos_node->left;
      this->transplant_node(pos_node, pos_node->left);
    } else {
      node* replace = (--pos).get_node();
      original_color = replace->color;
      new_parent = replace->left;
      if (replace->parent != pos_node) {
        this->transplant_node(replace, replace->left);
        replace->left = pos_node->left;
        replace->left->parent = replace;
      } else {
        new_parent->parent = replace;
      }
      this->transplant_node(pos_node, replace);
      replace->right = pos_node->right;
      replace->right->parent = replace;
      replace->color = pos_node->color;
    }

    if (original_color == BLACK) this->delete_fixup(new_parent);

    if (pos_node == this->anchor_->right) {
      this->anchor_->right = new_begin.get_node();
      new_begin.get_node()->left = this->anchor_;
    }

    if (pos_node == this->anchor_->left) {
      this->anchor_->left = new_end.get_node();
      new_end.get_node()->right = this->anchor_;
    }
    this->size_ -= 1;
    this->destroy_node(pos_node);
  }

  void erase(iterator first, iterator last) {
    iterator temp;
    while (first != last) {
      temp = first;
      ++first;
      this->erase(temp);
    }
  }

  void erase(const_iterator first, const_iterator last) {
    const_iterator temp;
    while (first != last) {
      temp = first;
      ++first;
      this->erase(temp);
    }
  }

  size_type erase(const key_type& key) {
    iterator target = this->find(key);
    if (!target.get_node()->value) {
      return 0;
    }
    this->erase(target);
    return 1;
  }

  void swap(rbtree& other) {
    key_compare temp_comparator_ = other.comparator_;
    allocator_type temp_value_allocator_ = other.value_allocator_;
    node_allocator_type temp_node_allocator_ = other.node_allocator_;
    extract temp_extractor_ = other.extractor_;
    node* temp_nil_ = other.nil_;
    node* temp_root_ = other.root_;
    node* temp_anchor_ = other.anchor_;
    size_type temp_size_ = other.size_;

    other.comparator_ = this->comparator_;
    other.value_allocator_ = this->value_allocator_;
    other.node_allocator_ = this->node_allocator_;
    other.extractor_ = this->extractor_;
    other.nil_ = this->nil_;
    other.root_ = this->root_;
    other.anchor_ = this->anchor_;
    other.size_ = this->size_;

    this->comparator_ = temp_comparator_;
    this->value_allocator_ = temp_value_allocator_;
    this->node_allocator_ = temp_node_allocator_;
    this->extractor_ = temp_extractor_;
    this->nil_ = temp_nil_;
    this->root_ = temp_root_;
    this->anchor_ = temp_anchor_;
    this->size_ = temp_size_;
  }

  //
  size_type count(const key_type& key) const {
    return (this->find(key) != this->end());
  }

  iterator find(const key_type& key) {
    node* result = this->root_;
    while (result->value) {
      if (this->comparator_(this->extractor_(result->value), key))
        result = result->right;
      else if (this->comparator_(key, this->extractor_(result->value)))
        result = result->left;
      else
        return iterator(result);
    }
    return this->end();
  }

  const_iterator find(const key_type& key) const {
    node* result = this->root_;
    while (result->value) {
      if (this->comparator_(this->extractor_(result->value), key))
        result = result->right;
      else if (this->comparator_(key, this->extractor_(result->value)))
        result = result->left;
      else
        return const_iterator(result);
    }
    return this->end();
  }

  ft::pair<iterator, iterator> equal_range(const key_type& key) {
    return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
  }

  ft::pair<const_iterator, const_iterator> equal_range(
      const key_type& key) const {
    return ft::make_pair(this->lower_bound(key), this->upper_bound(key));
  }

  iterator lower_bound(const key_type& key) {
    if (this->size_ == 0) {
      return (this->end());
    }
    node* result = this->root_;
    node* temp;
    while (result->value) {
      temp = result;
      if (this->comparator_(this->extractor_(result->value), key))
        result = result->right;
      else if (this->comparator_(key, this->extractor_(result->value)))
        result = result->left;
      else
        return iterator(temp);
    }
    while (!(this->comparator_(key, this->extractor_(temp->value))) &&
           temp != this->root_) {
      temp = temp->parent;
    }
    // if (temp == this->root_) {
    //   if (this->comparator_(this->extractor_(temp->value), key)) {
    //     return this->end();
    //   }
    //   if (this->comparator_(key, this->extractor_(temp->value))) {
    //     return iterator(temp);
    //   }
    // }
    if ((this->comparator_(key, this->extractor_(temp->value)))) {
      return iterator(temp);
    }
    return iterator(result);
  }

  const_iterator lower_bound(const key_type& key) const {
    if (this->size_ == 0) {
      return (this->end());
    }
    node* result = this->root_;
    node* temp;
    while (result->value) {
      temp = result;
      if (this->comparator_(this->extractor_(result->value), key)) {
        result = result->right;
      } else if (this->comparator_(key, this->extractor_(result->value))) {
        result = result->left;
      } else {
        return const_iterator(temp);
      }
    }
    while (!(this->comparator_(key, this->extractor_(temp->value))) &&
           temp != this->root_) {
      temp = temp->parent;
    }
    // if (temp == this->root_) {
    //   if (this->comparator_(this->extractor_(temp->value), key)) {
    //     return this->end();
    //   }
    //   if (this->comparator_(key, this->extractor_(temp->value))) {
    //     return const_iterator(temp);
    //   }
    // }
    if ((this->comparator_(key, this->extractor_(temp->value)))) {
      return const_iterator(temp);
    }
    return const_iterator(result);
  }

  iterator upper_bound(const key_type& key) {
    if (this->size_ == 0) {
      return (this->end());
    }
    node* result = this->root_;
    node* temp;
    while (result->value) {
      temp = result;
      if (this->comparator_(key, this->extractor_(result->value)))
        result = result->left;
      else
        result = result->right;
    }
    while (!(this->comparator_(key, this->extractor_(temp->value))) &&
           temp != this->root_) {
      temp = temp->parent;
    }
    // if (temp == this->root_) {
    //   if (this->comparator_(key, this->extractor_(temp->value))) {
    //     return iterator(temp);
    //   } else {
    //     return this->end();
    //   }
    // }
    if ((this->comparator_(key, this->extractor_(temp->value)))) {
      return iterator(temp);
    }
    return iterator(result);
  }

  const_iterator upper_bound(const key_type& key) const {
    if (this->size_ == 0) {
      return (this->end());
    }
    node* result = this->root_;
    node* temp;
    while (result->value) {
      temp = result;
      if (this->comparator_(key, this->extractor_(result->value)))
        result = result->left;
      else
        result = result->right;
    }
    while (!(this->comparator_(key, this->extractor_(temp->value))) &&
           temp != this->root_) {
      temp = temp->parent;
    }
    // if (temp == this->root_) {
    //   if (this->comparator_(key, this->extractor_(temp->value))) {
    //     return const_iterator(temp);
    //   } else {
    //     return this->end();
    //   }
    // }
    if ((this->comparator_(key, this->extractor_(temp->value)))) {
      return const_iterator(temp);
    }
    return const_iterator(result);
  }

  key_compare key_comp() const { return this->comparator_; }

 private:
  node* init_node(const_reference value) {
    node* ret = this->node_allocator_.allocate(1);
    ret->parent = nil_;
    ret->left = nil_;
    ret->right = nil_;
    ret->value = this->value_allocator_.allocate(1);
    this->value_allocator_.construct(ret->value, value);
    ret->color = RED;
    return ret;
  }

  node* init_nil() {
    node* ret = this->node_allocator_.allocate(1);
    ret->parent = NULL;
    ret->left = NULL;
    ret->right = NULL;
    ret->value = NULL;
    ret->color = BLACK;
    return ret;
  }

  void destroy_node(node* target) {
    this->value_allocator_.destroy(target->value);
    this->value_allocator_.deallocate(target->value, 1);
    this->node_allocator_.deallocate(target, 1);
  }

  bool compare(node* n1, node* n2) {
    return this->comparator_(this->extractor_(n1->value),
                             this->extractor_(n2->value));
  }

  void clear_all_node(node* node) {
    if (!node->value) return;

    clear_all_node(node->left);
    clear_all_node(node->right);
    destroy_node(node);
  }

  /// node->right >>> parent
  /// node->right->left >>> node->right
  /// node->right->left >>> node
  void leftrotate(node* cur_node) {
    node* new_parent = cur_node->right;

    cur_node->right = new_parent->left;
    new_parent->left->parent = cur_node;

    new_parent->parent = cur_node->parent;
    if (!cur_node->parent->value)
      this->root_ = new_parent;
    else if (cur_node == cur_node->parent->left)
      cur_node->parent->left = new_parent;
    else
      cur_node->parent->right = new_parent;

    new_parent->left = cur_node;
    cur_node->parent = new_parent;
  }

  void rightrotate(node* cur_node) {
    node* new_parent = cur_node->left;

    cur_node->left = new_parent->right;
    new_parent->right->parent = cur_node;

    new_parent->parent = cur_node->parent;
    if (!cur_node->parent->value)
      this->root_ = new_parent;
    else if (cur_node == cur_node->parent->left)
      cur_node->parent->left = new_parent;
    else
      cur_node->parent->right = new_parent;

    new_parent->right = cur_node;
    cur_node->parent = new_parent;
  }

  void insert_root(const_reference value) {
    this->root_ = init_node(value);
    this->root_->color = BLACK;
    this->root_->left = this->anchor_;
    this->root_->right = this->anchor_;
    this->root_->parent = this->anchor_;
    this->anchor_->left = this->root_;
    this->anchor_->right = this->root_;
    ++(this->size_);
  }

  void insert_fixup(node* new_node) {
    node* uncle;
    while (new_node->parent->color == RED) {
      if (new_node->parent == new_node->parent->parent->left) {
        uncle = new_node->parent->parent->right;
        if (uncle->color == RED) {
          new_node->parent->color = BLACK;
          uncle->color = BLACK;
          new_node->parent->parent->color = RED;
          new_node = new_node->parent->parent;
        } else {
          if (new_node == new_node->parent->right) {
            new_node = new_node->parent;
            leftrotate(new_node);
          }
          new_node->parent->color = BLACK;
          new_node->parent->parent->color = RED;
          rightrotate(new_node->parent->parent);
        }
      } else {
        uncle = new_node->parent->parent->left;
        if (uncle->color == RED) {
          new_node->parent->color = BLACK;
          uncle->color = BLACK;
          new_node->parent->parent->color = RED;
          new_node = new_node->parent->parent;
        } else {
          if (new_node == new_node->parent->left) {
            new_node = new_node->parent;
            rightrotate(new_node);
          }
          new_node->parent->color = BLACK;
          new_node->parent->parent->color = RED;
          leftrotate(new_node->parent->parent);
        }
      }
    }
    this->root_->color = BLACK;
  }

  void update_anchor() {
    if (this->anchor_->right->left->value) {
      this->anchor_->right = this->anchor_->right->left;
      this->anchor_->right->left = this->anchor_;
    }
    if (this->anchor_->left->right->value) {
      this->anchor_->left = this->anchor_->left->right;
      this->anchor_->left->right = this->anchor_;
      this->anchor_->parent = this->anchor_->left;
    }
  }

  void transplant_node(node* dest, node* src) {
    if (this->root_ == dest)
      this->root_ = src;
    else if (dest == dest->parent->left)
      dest->parent->left = src;
    else
      dest->parent->right = src;
    src->parent = dest->parent;
  }

  void delete_fixup(node* cur_node) {
    node* brother;
    while ((cur_node != this->root_) && (cur_node->color == BLACK)) {
      if (cur_node == cur_node->parent->left) {
        brother = cur_node->parent->right;
        if (brother->color == RED) {  // case 2
          brother->color = BLACK;
          cur_node->parent->color = RED;
          this->leftrotate(cur_node->parent);
          brother = cur_node->parent->right;
        }
        if ((brother->left->color == BLACK) &&  // case 3, 4
            (brother->right->color == BLACK)) {
          // cur_node->parent->color = BLACK;  ///
          brother->color = RED;
          cur_node = cur_node->parent;
        } else {
          if (brother->right->color == BLACK) {  // case 5
            brother->left->color = BLACK;
            brother->color = RED;
            this->rightrotate(brother);
            brother = cur_node->parent->right;
          }
          brother->color = cur_node->parent->color;  // case 6
          cur_node->parent->color = BLACK;
          brother->right->color = BLACK;
          this->leftrotate(cur_node->parent);
          cur_node = this->root_;
        }
      } else {
        brother = cur_node->parent->left;
        if (brother->color == RED) {
          brother->color = BLACK;
          cur_node->parent->color = RED;
          this->rightrotate(cur_node->parent);
          brother = cur_node->parent->left;
        }

        if ((brother->left->color == BLACK) &&
            (brother->right->color == BLACK)) {
          // cur_node->parent->color = BLACK;  ////
          brother->color = RED;
          cur_node = cur_node->parent;
        } else {
          if (brother->left->color == BLACK) {
            brother->right->color = BLACK;
            brother->color = RED;
            this->leftrotate(brother);
            brother = cur_node->parent->left;
          }

          brother->color = cur_node->parent->color;
          cur_node->parent->color = BLACK;
          brother->left->color = BLACK;
          this->rightrotate(cur_node->parent);
          cur_node = this->root_;
        }
      }
    }
    cur_node->color = BLACK;
  }
};

#endif