#include "RleString.h"

// TODO Write your implementation here

RleString::RleString() : head(nullptr), tail(nullptr)
{
}

RleString::RleString(const std::string& str)
{
	int strLength = str.length();
	if (strLength == 0) {
		return;
	}
	try {

		for (int i = 0; i < strLength; i++) {

			int count = 1;
			while (i < strLength - 1 && str[i] == str[i + 1]) {
				count++;
				i++;
			}

			Node* newNode = new Node(str[i], count, nullptr);

			if (this->head == nullptr) {
				this->head = newNode;
				this->tail = newNode;
			}
			else {
				this->tail->next = newNode;
				this->tail = newNode;
			}
		}
	}
	catch (std::bad_alloc& ba) {
		clear();
		this->head = nullptr;
		this->tail = nullptr;
		throw;
	}

}

RleString::RleString(const RleString& other)
{
	size_t position = 0;
	Node* traverseOther = other.head;
	while (traverseOther) {
		insertAt(position, traverseOther->symbol);
		position++;
		traverseOther = traverseOther->next;
	}
}

RleString& RleString::operator=(const RleString& other)
{
	if (*this == other) {
		return *this;
	}

	clear();
	size_t position = 0;
	Node* traverseOther = other.head;
	while (traverseOther) {
		insertAt(position, traverseOther->symbol);
		position++;
		traverseOther = traverseOther->next;
	}

	return *this;
}

RleString::~RleString()
{
	clear();
}

std::string RleString::toString() const
{
	std::string result;
	Node* currentNode = this->head;
	while (currentNode)
	{
		result += std::string(currentNode->count, currentNode->symbol);
		currentNode = currentNode->next;
	}
	return result;
}

bool RleString::operator==(const RleString& other) const
{
	if (this->size() != other.size()) {
		return false;
	}
	Node* currentNode = this->head;
	Node* otherNode = other.head;
	while (currentNode && otherNode)
	{
		if (currentNode->count != otherNode->count
			|| currentNode->symbol != otherNode->symbol)
			return false;
		currentNode = currentNode->next;
		otherNode = otherNode->next;
	}
	return true;
}

bool RleString::operator==(const std::string& str) const
{
	RleString strToCompare(str);
	return *this == strToCompare;
}

size_t RleString::size() const noexcept
{
	size_t counter = 0;
	Node* currentNode = this->head;
	while (currentNode) {
		counter += currentNode->count;
		currentNode = currentNode->next;
	}
	return counter;
}

void RleString::insertAt(size_t index, char value)
{
	Node* currentNode = this->head;
	Node* previousNode = nullptr;
	while (currentNode && index >= currentNode->count) {
		index -= currentNode->count;
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode == nullptr) {
		if (index > 0) {
			throw std::out_of_range("Invalid index.");
		}
		if (previousNode == nullptr) {
			Node* nodeToInsert = new Node(value, 1, nullptr);
			this->head = nodeToInsert;
			return;
		}
		else {
			if (previousNode->symbol == value) {
				previousNode->count++;
				return;
			}
			Node* nodeToInsert = new Node(value, 1, currentNode);
			previousNode->next = nodeToInsert;
			return;
		}
	}
	if (index == 0) {
		if (currentNode->symbol == value) {
			currentNode->count++;
			return;
		}
		else {
			Node* nodeToInsert = new Node(value, 1, currentNode);
			if (previousNode == nullptr) {
				this->head = nodeToInsert;
				return;
			}
			previousNode->next = nodeToInsert;
			return;
		}
	}
	else {
		Node* newNode = new Node(currentNode->symbol, currentNode->count - index, currentNode->next);
		Node* nodeToInsert = new Node(value, 1, newNode);
		currentNode->count = index;
		currentNode->next = nodeToInsert;
		return;
	}

}

void RleString::removeAt(size_t index)
{
	Node* currentNode = this->head;
	Node* previousNode = nullptr;
	while (currentNode && index >= currentNode->count) {
		index -= currentNode->count;
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode == nullptr) {
		throw std::out_of_range("Invalid index.");
	}
	if (currentNode->count > 1) {
		currentNode->count--;
		return;
	}
	else if (previousNode == nullptr) {

		this->head = currentNode->next;
		delete currentNode;
	}
	else {
		previousNode->next = currentNode->next;
		delete currentNode;
	}
}

void RleString::reverse()
{
	Node* front = this->head;
	Node* nxt = nullptr;
	Node* prev = nullptr;

	while (front) {

		nxt = front->next;
		front->next = prev;
		prev = front;
		front = nxt;
	}
	this->head = prev;
}

bool RleString::contains(const RleString& rle) const
{
	Node* otherNode = rle.head;
	Node* currentNode = this->head;

	if (*this == rle) {
		return true;
	}

	if ((currentNode == nullptr && otherNode == nullptr) || (currentNode != nullptr && otherNode == nullptr)) {
		return true;
	}

	if (currentNode == nullptr) {
		return false;
	}

	while (currentNode) {

		while (otherNode) {

			size_t position = 0;
			if (currentNode == nullptr) {
				return false;
			}
			else if (otherNode->symbol == currentNode->symbol && otherNode->count <= currentNode->count) {
				if (position == 0) {
					otherNode = otherNode->next;
					currentNode = currentNode->next;
					position++;
				}
				else if (otherNode->next && currentNode->count != otherNode->count) {
					return false;
				}
			}
			else {
				break;
			}
		}
		if (otherNode == nullptr)
			return true;

		otherNode = rle.head;

		currentNode = currentNode->next;

	}
	return false;
}

void RleString::clear()
{
	while (this->head) {

		Node* currentNode = this->head;
		this->head = this->head->next;
		delete currentNode;
	}
}
