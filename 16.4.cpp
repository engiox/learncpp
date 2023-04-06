#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <functional>

class Patient;

class Doctor
{
    std::string m_name{};
    std::vector<std::reference_wrapper<const Patient>> m_patient{};

public:
    Doctor(const std::string& name) : m_name{ name } {}
    void addPatient(Patient& patient);
    friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);
    const std::string& getName() const { return m_name; }
};

class Patient
{
    std::string m_name{};
    std::vector<std::reference_wrapper<const Doctor>> m_doctor{};

    void addDoctor(const Doctor& doctor)
    {
        m_doctor.push_back(doctor);
    }

public:
    Patient(const std::string& name) : m_name{ name } {}
    friend std::ostream& operator<<(std::ostream& out, const Patient& patient);
    const std::string& getName() const { return m_name; }
    friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
    m_patient.push_back(patient);
    patient.addDoctor(*this);
}

std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
{
    if (doctor.m_patient.empty()) {
        out << doctor.getName() << " has no patient right now.";
        return out;
    }

    out << doctor.getName() << " is seeing patients: ";
    for (const auto& patient : doctor.m_patient) {
        out << patient.get().getName() << ' ';
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient)
{
    if (patient.m_doctor.empty()) {
        out << patient.getName() << " has no doctors right now.";
        return out;
    }

    out << patient.getName() << " is seeing doctors: ";
    for (const auto& patient : patient.m_doctor) {
        out << patient.get().getName() << ' ';
    }

    return out;
}

class Car
{
    std::string m_name{};
    int m_id{};
public:
    Car(const std::string& name, int id) : m_name{ name }, m_id{ id } {}
    const std::string& getName() const { return m_name; }
    int getID() const { return m_id; }
};

class CarLot
{
    static Car s_carLot[4];

public:
    CarLot() = delete;
};

void p1()
{
	// Create a Patient outside the scope of the Doctor
	Patient dave{ "Dave" };
	Patient frank{ "Frank" };
	Patient betsy{ "Betsy" };

	Doctor james{ "James" };
	Doctor scott{ "Scott" };

	james.addPatient(dave);

	scott.addPatient(dave);
	scott.addPatient(betsy);

	std::cout << james << '\n';
	std::cout << scott << '\n';
	std::cout << dave << '\n';
	std::cout << frank << '\n';
	std::cout << betsy << '\n';
}

void p2()
{
}

int main()
{
    p1();
    p2();

	return 0;
}
