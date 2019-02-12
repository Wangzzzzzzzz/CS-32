/*Base class*/
////////////////////////*Concern*//////////////////////////
class Concern {
public:
	Concern(string name);
	string person() const;
	virtual string description() const = 0;
	virtual bool possibleFelony() const;
	virtual ~Concern();
private:
	string m_person;
};

Concern::~Concern()
{}

Concern::Concern(string name)
	:m_person(name)
{}

string Concern::person() const
{
	return m_person;
}

bool Concern::possibleFelony() const
{
	return false;
}
///////////////////*End of Concern*/////////////////////

/*Derived classes*/
/////////////////////*EthicsMatter*/////////////////////
class EthicsMatter : public Concern {
public:
	EthicsMatter(string name);
	virtual string description() const;
	virtual ~EthicsMatter();
private:
};

EthicsMatter::EthicsMatter(string name)
	:Concern(name)
{}

string EthicsMatter::description() const {
	return "An ethics matter";
}

EthicsMatter::~EthicsMatter() {
	cout << "Destroying " << this->person() << "'s ethics matter" << endl;
}
/////////////////////*End of EthicsMatter*/////////////////////

/////////////////////*HushPayment*/////////////////////
class HushPayment : public Concern {
public:
	HushPayment(string name, int money);
	virtual string description() const;
	virtual ~HushPayment();
private:
	int m_money;
};

HushPayment::HushPayment(string name, int money)
	:Concern(name),m_money(money)
{}

string HushPayment::description() const {
	return ("A $" + to_string(this->m_money) + " payment");
}

HushPayment::~HushPayment() {
	cout << "Destroying " << this->person() << "'s hush payment" << endl;
}
/////////////////////*End of HushPayment*/////////////////////

/////////////////////*Investigation*/////////////////////
class Investigation : public Concern {
public:
	Investigation(string name);
	virtual string description() const;
	virtual bool possibleFelony() const;
	virtual ~Investigation();
private:
};

Investigation::Investigation(string name)
	:Concern(name)
{}

string Investigation::description() const {
	return "An investigation";
}

bool Investigation::possibleFelony() const {
	return true;
}

Investigation::~Investigation() {
	cout << "Destroying " << this->person() << "'s investigation" << endl;
}
/////////////////////*End ofInvestigation*/////////////////////