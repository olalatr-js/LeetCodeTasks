#include <memory>

template <typename T>
struct Node
{
	T data;
	Node* left{nullptr};
	Node* right{ nullptr };

	Node(T key) : data(key) {}

	~Node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

template <typename T>
class BinST
{
public:
	BinST() = default;
	bool Contains(T key)
	{
		auto curr = m_root.get();
		while (curr)
		{
			if (curr->data == key)
				return true;
			else if (key < curr->data)
				curr = curr->left;
			else
				curr = curr->right;
		}

		return false;
	}

	void Insert(T key)
	{
		if (!m_root)
			m_root = std::make_unique<Node<T>>(key);

		auto curr = m_root.get();
		while (true)
		{
			if (key < curr->data)
			{
				if (curr->left)
					curr = curr->left;
				else
				{
					curr->left = new Node<T>(key);
					break;
				}
			}
			else
			{
				if (curr->right)
					curr = curr->right;
				else
				{
					curr->right = new Node<T>(key);
					break;
				}
			}
		}
	}

	void Erase(T key)
	{

	}
private:
	std::unique_ptr<Node<T>> m_root;
};

void BinST_func()
{
	BinST<int> st;
	st.Insert(5);
}