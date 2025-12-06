create table if not exists DEPARTMENT (
	dept_id int primary key,
	name text
);

create table if not exists DOCTOR (
	doctor_id int primary key,
	dept_id int references DEPARTMENT(dept_id) 
		on delete cascade on update cascade,
	full_name text,
	contact text
);

create table if not exists SURGEON (
	doctor_id int primary key references DOCTOR(doctor_id)
				on delete cascade on update cascade,
	speciality text not null,
	surgical_license text unique
);

create table if not exists NURSE (
	doctor_id int primary key references DOCTOR(doctor_id)
				on delete cascade on update cascade,
	shift text default 'DAY' check (shift in ('DAY', 'NIGHT', 'ROTATION'))
);

create table if not exists PATIENT (
	patient_id int primary key,
	full_name text,
	contact text,
	address text default 'Not provided'
);

create table if not exists EMERGENCY_CONTACT (
	patient_id int references PATIENT(patient_id)
				on delete cascade on update cascade,
	em_contact_id int,
	full_name text,
	contact text,
	"relation" check (relation in ('PARENT', 'SIBLING', 'FRIEND', 'SPOUSE', 'OTHER')),
	constraint pk_emergency_contact primary key(patient_id, em_contact_id)
);

create table if not exists SURGERY (
	surgeon_id int references SURGEON(doctor_id)
				on delete cascade on update cascade,
	nurse_id int references NURSE(doctor_id)
				on delete cascade on update cascade,
	patient_id int references PATIENT(patient_id) 
			on delete set null on update cascade,
	time text,
	procedure nvarchar(500) not null,
	constraint pk_surgery primary key(surgeon_id, nurse_id, patient_id)
);

create table if not exists CHECK_UP (
    nurse_id int default -1,
    patient_id int,
    check_date text,
    diagnosis text,

    constraint check_date_constraint check ((check_date glob
                                 '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]') and
                                 check_date like '2025-%'),
    constraint pk_check_up primary key (nurse_id,patient_id,check_date),
    constraint fk_nurse foreign key (nurse_id) references NURSE(doctor_id)
                      on delete set default on update cascade ,
    constraint fk_patient foreign key (patient_id) references PATIENT(patient_id)
                      on delete cascade on update cascade

);

create table if not exists PRESCRIPTIONS (
	nurse_id int,
	patient_id int,
	check_date text,
	prescription text,
	dosage text,
	constraint dosage_type check (
		(prescription like '%fluid%' and dosage like '%ml') or
		(prescription like '%tablet%' and dosage like '%mg')
	),
	constraint fk_all foreign key (nurse_id,patient_id,check_date)
		references CHECK_UP(nurse_id,patient_id,check_date)
		on delete cascade on update cascade,
	constraint pk_prescriptions primary key(nurse_id, patient_id, check_date, prescription)
);

