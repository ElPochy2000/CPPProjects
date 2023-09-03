#ifndef STREAMABLE_H
#define STREMABLE_H

namespace sdds {
	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& os)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;

		virtual bool conIO(std::ios& io)const = 0;
		virtual operator bool()const = 0;

		virtual ~Streamable() {};
	};

	std::ostream& operator<<(std::ostream& os, const Streamable& stream);
	std::istream& operator>>(std::istream& is, Streamable& stream);
}

#endif // !STREAMABLE_H
