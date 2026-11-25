#ifndef Spine_SpineTextureRef_h
#define Spine_SpineTextureRef_h

#include <cstdint>
#include <cstddef>

namespace spine {

// Stores a texture_stream::TextureHandle address. gl_name is that object's first field.
// A read resolves to the current GL name, or null when the name is 0. The name is not copied here.
struct SpineTextureRef {
	void* handle{nullptr};

	SpineTextureRef() = default;
	SpineTextureRef(std::nullptr_t) : handle(nullptr) {}

	SpineTextureRef& operator=(std::nullptr_t)
	{
		handle = nullptr;
		return *this;
	}

	void* resolved() const
	{
		if (handle == nullptr)
			return nullptr;
		const auto name = *reinterpret_cast<const std::uint64_t*>(handle);
		if (name == 0)
			return nullptr;
		return reinterpret_cast<void*>(static_cast<std::uintptr_t>(name));
	}

	operator void*() const { return resolved(); }

	friend bool operator==(const SpineTextureRef& left, const SpineTextureRef& right)
	{ return left.resolved() == right.resolved(); }

	friend bool operator==(const SpineTextureRef& left, void* right)
	{ return left.resolved() == right; }

	friend bool operator==(void* left, const SpineTextureRef& right)
	{ return left == right.resolved(); }

	friend bool operator==(const SpineTextureRef& left, std::nullptr_t)
	{ return left.resolved() == nullptr; }

	friend bool operator==(std::nullptr_t, const SpineTextureRef& right)
	{ return right.resolved() == nullptr; }

	friend bool operator!=(const SpineTextureRef& left, const SpineTextureRef& right)
	{ return !(left == right); }

	friend bool operator!=(const SpineTextureRef& left, void* right)
	{ return !(left == right); }

	friend bool operator!=(void* left, const SpineTextureRef& right)
	{ return !(left == right); }

	friend bool operator!=(const SpineTextureRef& left, std::nullptr_t)
	{ return !(left == nullptr); }

	friend bool operator!=(std::nullptr_t, const SpineTextureRef& right)
	{ return !(nullptr == right); }
};

}

#endif
