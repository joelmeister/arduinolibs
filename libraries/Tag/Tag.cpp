
Tag::Tag(){
	Tag(false);
}
Tag::Tag(bool i)
: it(i)
{}
Tag::~Tag(){}
bool Tag::isIt(){
	return this->it;
}
void Tag::tagged(){
	this->it = true;
}
