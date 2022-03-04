#pragma once

template<typename bits>
class numN
{
    protected:
	bits val;

    public:
	numN(bits val);
	virtual ~numN() = 0;
};

template<typename bits>
class num3 : private numN<bits>
{
    public:
	num3(bits val) : val{val & 0b111} {}

template<typename bits>
class num5 : private numN<bits>
{
    public:
	num5(bits val) : val{val & 0b11111} {}

template<typename bits>
class num6 : private numN<bits>
{
    public:
	num6(bits val) : val{val & 0b111111} {}

template<typename bits>
class num9 : private numN<bits>
{
    public:
	num9(bits val) : val{val & 0b111111111} {}

template<typename bits>
class num11 : private numN<bits>
{
    public:
	num11(bits val) : val{val & 0b11111111111} {}
};
