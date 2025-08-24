#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ========== ENUMERATIONS ========== //
enum Department
{
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType
{
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== PATIENT CLASS ========== //
class Patient
{
private:
    int id;
    string name;
    int age;
    string contact;
    stack<string> medicalHistory;
    queue<string> testQueue;
    bool isAdmitted;
    RoomType roomType;

public:
    Patient(int pid, string n, int a, string c);

    void admitPatient(RoomType type);
    void dischargePatient();
    void addMedicalRecord(string record);
    void requestTest(string testName);
    string performTest();
    void displayHistory();

    int getId();
    string getName();
    bool getAdmissionStatus();
};

// ========== DOCTOR CLASS ========== //
class Doctor
{
private:
    int id;
    string name;
    Department department;
    queue<int> appointmentQueue;

public:
    Doctor(int did, string n, Department d)
    {
        id = did;
        name = n;
        department = d;
    }

    void addAppointment(int patientId)
    {
        appointmentQueue.push(patientId);
    }

    int seePatient()
    {
        if (appointmentQueue.empty())
        {
            return -1; // مفيش مرضى
        }
        int nextPatient = appointmentQueue.front();
        appointmentQueue.pop();
        return nextPatient;
    }

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    Department getDepartment()
    {
        return department;
    }
};
// ========== HOSPITAL CLASS ========== //
class Hospital
{
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    queue<int> emergencyQueue;
    int patientCounter;
    int doctorCounter;

public:
    Hospital(){
        patientCounter=0;
        doctorCounter=0;
    }

    int addDoctor(string name, Department dept)
    {
        int result =0;
        bool IfExist
        {
            for (int i=0;i<doctors.size();i++)
                {
                    if(doctors[i].getName() == name)
                    {
                        result=i+1;
                         return true;
                    }

                }

        }
        if(IfExist == false )
        {
            doctorCounter++;
            doctors.push_back(Doctor(doctorCounter,name,dept));
            result=doctorCounter;
        }
        return result;
    }
    void admitPatient(int patientId, RoomType type);
    int registerPatient(string name, int age, string contact)
    {
        for (int i = 0; i < patients.size(); i++)
        {
            if (patients[i].getName() == name)
            {
                cout << "this patient already exists  " << endl;
                return (i + 1);
            }
        }
        patientCounter++;
        patients.push_back(Patient(patientCounter, name, age, contact));
        return patientCounter;//(مش المفروض تكون ال patient id ?)
    }
    void addEmergency(int patientId)
    {
        emergencyQueue.push(patientId);
    }
    int handleEmergency()
    {
        if (emergencyQueue.empty())
        {
            cout << "No emergency cases...." << endl;
            return -1;
        }
        else
        {
            int v = emergencyQueue.front();
            emergencyQueue.pop();
            cout << "Patient with ID" << v << "has been handeled";
        }
    }
    void bookAppointment(int doctorId, int patientId)
    {
        if (doctorId > doctors.size())
        {
            cout << "the doctorid is not valid...." << endl;
            return;
        }
        if (patientId > patients.size())
        {
            cout << "the patientid is not valid...." << endl;
            return;
        }
        doctors[doctorId - 1].addAppointment(patientId);
    }
    void displayPatientInfo(int patientId)
    {
        if (patientId <= patients.size())
        {
            cout << "The patient's Name:   " << patients[patientId - 1].getName() << endl;
            cout << "The patient's ID:   " << patients[patientId - 1].getId() << endl;
            cout << "The patient's Admission status is:   " << patients[patientId - 1].getAdmissionStatus() << endl;
            cout << "The patient's Name:   " << patients[patientId - 1].displayHistory() << endl;
        }
        else
        {
            cout << "Invalid patient's ID " << endl;
        }
    }
    void displayDoctorInfo(int doctorId)
    {
        if (doctorId <= doctors.size())
        {
            cout << "The Doctor Name :   " << doctors[doctorId - 1].getName() << "              ";
            cout << "The Doctor Department :   " << doctors[doctorId - 1].getDepartment() << endl;
        }
        else
        {
            cout << "invalid doctorid  " << endl;
        }
    }
};

// ========== MAIN PROGRAM ========== //
int main()
{
    Hospital hospital;

    // Test Case 1: Registering patients
    int p1 = hospital.registerPatient("John Doe", 35, "555-1234");
    int p2 = hospital.registerPatient("Jane Smith", 28, "555-5678");
    int p3 = hospital.registerPatient("Mike Johnson", 45, "555-9012");

    // Test Case 2: Adding doctors
    int d1 = hospital.addDoctor("Dr. Smith", CARDIOLOGY);
    int d2 = hospital.addDoctor("Dr. Brown", NEUROLOGY);
    int d3 = hospital.addDoctor("Dr. Lee", PEDIATRICS);

    // Test Case 3: Admitting patients
    hospital.admitPatient(p1, PRIVATE_ROOM);
    hospital.admitPatient(p2, ICU);
    // Try admitting already admitted patient
    hospital.admitPatient(p1, SEMI_PRIVATE);

    // Test Case 4: Booking appointments
    hospital.bookAppointment(d1, p1);
    hospital.bookAppointment(d1, p2);
    hospital.bookAppointment(d2, p3);
    // Try booking with invalid doctor/patient
    hospital.bookAppointment(999, p1); // Invalid doctor
    hospital.bookAppointment(d1, 999); // Invalid patient

    // Test Case 5: Handling medical tests
    // These would normally be called on Patient objects
    // In a real implementation, we'd need a way to access patients

    // Test Case 6: Emergency cases
    hospital.addEmergency(p3);
    hospital.addEmergency(p1);
    int emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency();
    emergencyPatient = hospital.handleEmergency(); // No more emergencies

    // Test Case 7: Discharging patients
    // Would normally call dischargePatient() on Patient objects

    // Test Case 8: Displaying information
    hospital.displayPatientInfo(p1);
    hospital.displayPatientInfo(p2);
    hospital.displayPatientInfo(999); // Invalid patient

    hospital.displayDoctorInfo(d1);
    hospital.displayDoctorInfo(d2);
    hospital.displayDoctorInfo(999); // Invalid doctor

    // Test Case 9: Doctor seeing patients
    // These would normally be called on Doctor objects
    // In a real implementation, we'd need a way to access doctors

    // Test Case 10: Edge cases
    Hospital emptyHospital;
    emptyHospital.displayPatientInfo(1); // No patients
    emptyHospital.displayDoctorInfo(1);  // No doctors
    emptyHospital.handleEmergency();     // No emergencies

    return 0;
}

