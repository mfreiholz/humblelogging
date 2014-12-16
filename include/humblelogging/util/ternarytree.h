#ifndef TERNARYTREE_H
#define TERNARYTREE_H

#include <vector>

HL_NAMESPACE_BEGIN

template <class V>
class TernaryNode
{
public:
  TernaryNode(char c, bool end)
    : _c(c),
      _end(end),
      _low(NULL),
      _equal(NULL),
      _high(NULL),
      _parent(NULL)
  {}

  ~TernaryNode()
  {}

public:
  char _c;
  bool _end;
  V _value;
  TernaryNode<V> *_low, *_equal, *_high, *_parent;
};


template <class V>
class TernaryTree
{
public:
  TernaryTree()
    : _root(NULL)
  {}

  ~TernaryTree()
  {
    deleteNode(_root);
    _root = NULL;
  }

  // Insertion based methods //////////////////////////////////////////////////

  void insert(char *key, V value)
  {
    _root = insert(key, value, _root);
  }

  TernaryNode<V>* insert(char *key, V value, TernaryNode<V> *node, TernaryNode<V> *parent = NULL)
  {
    if (!node) {
      char c = *key;
      node = new TernaryNode<V>(c, false);
      node->_parent = parent;
    }
    if (*key < node->_c) {
      node->_low = insert(key, value, node->_low);
    } else if (*key == node->_c) {
      if (*++key == 0) {
        node->_value = value;
        node->_end = true;
      } else {
        node->_equal = insert(key, value, node->_equal);
      }
    } else {
      node->_high = insert(key, value, node->_high);
    }
    return node;
  }

  // Basic find nodes based methods ///////////////////////////////////////////

  TernaryNode<V>* findNode(char *key) const
  {
    return findNode(key, _root);
  }

  TernaryNode<V>* findNodeEnd(char *key) const
  {
    TernaryNode<V> *n = findNode(key, _root);
    if (n && n->_end)
      return n;
    return NULL;
  }

  TernaryNode<V>* findNode(char *key, TernaryNode<V> *node) const
  {
    if (!node)
      return NULL;
    if (*key < node->_c) {
      return findNode(key, node->_low);
    } else if (*key == node->_c) {
      if (*++key == 0) {
        return node;
      } else {
        return findNode(key, node->_equal);
      }
    } else {
      return findNode(key, node->_high);
    }
  }

  // Nearest search based methods /////////////////////////////////////////////

  struct FindNodePathData {
    std::vector<TernaryNode<V>*> _nodes;
  };

  TernaryNode<V>* findNodePath(char *key, FindNodePathData &data) const
  {
    return findNodePath(key, _root, data);
  }

  TernaryNode<V>* findNodePath(char *key, TernaryNode<V> *node, FindNodePathData &data) const
  {
    if (!node)
      return NULL;
    if (*key < node->_c) {
      data._nodes.push_back(node);
      return findNodePath(key, node->_low, data);
    } else if (*key == node->_c) {
      if (*++key == 0) {
        data._nodes.push_back(node);
        return node;
      } else {
        data._nodes.push_back(node);
        return findNodePath(key, node->_equal, data);
      }
    } else {
      data._nodes.push_back(node);
      return findNodePath(key, node->_high, data);
    }
  }

  // Prefix search based methods //////////////////////////////////////////////

  struct FindNodePrefixData {
    std::vector<TernaryNode<V>*> _nodes;
  };

  std::vector<V> findNodeEndValuesByPrefix(char *key, unsigned int max = 0) const
  {
    std::vector<TernaryNode<V>*> nodes = findNodeEndsByPrefix(key, max);
    std::vector<V> values;
    for (size_t i = 0; i < nodes.size(); ++i) {
      values.push_back(nodes[i]->_value);
    }
    return values;
  }

  std::vector<TernaryNode<V>*> findNodeEndsByPrefix(char *key, unsigned int max = 0) const
  {
    FindNodePrefixData data;
    TernaryNode<V> *begin = findNode(key, _root);
    if (begin) {
      findNodeEndsByPrefixTraverse(begin, max, data);
    }
    return data._nodes;
  }

  void findNodeEndsByPrefixTraverse(TernaryNode<V> *node, unsigned int max, FindNodePrefixData &data) const
  {
    if (max != 0 && data._nodes.size() >= max) {
      return;
    } else if (node->_end) {
      data._nodes.push_back(node);
    }
    
    if (node->_low)
      findNodeEndsByPrefixTraverse(node->_low, max, data);
    if (node->_equal)
      findNodeEndsByPrefixTraverse(node->_equal, max, data);
    if (node->_high)
      findNodeEndsByPrefixTraverse(node->_high, max, data);
  }

protected:
  virtual void deleteNode(TernaryNode<V> *begin)
  {
    std::vector<TernaryNode<V>*> vec;
    vec.push_back(begin);
    while (!vec.empty()) {
      TernaryNode<V> *node = vec.at(vec.size() - 1);
      vec.pop_back();
      if (node->_low)
        vec.push_back(node->_low);
      if (node->_equal)
        vec.push_back(node->_equal);
      if (node->_high)
        vec.push_back(node->_high);
      delete node;
    }
  }

protected:
  TernaryNode<V> *_root;
};

HL_NAMESPACE_END
#endif
