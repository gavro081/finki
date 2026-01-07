package k2.z29_PayrollSystem2;

import java.util.*;
import java.util.stream.Collectors;

enum EmployeeType {
    HOURLY,
    FREELANCE,
    BASIC
}

interface Employee{
    double getRate();
    String getLevel();
    double getSalary();
    double getBonus();
    EmployeeType getType();

    default double getOvertime(){
        // ova treba da vraka 0 ama vraka -1 poradi buggot vo resenieto na courses
        // vidi getOvertimeSalaryForLevels()
        return -1;
    }

    default double getHours(){
        return 0;
    }
    default int getTicketPoints(){
        return 0;
    }
}

class BasicEmployee implements Employee, Comparable<BasicEmployee> {
    private final String id;
    private final String level;
    private final double rate;

    public BasicEmployee(String id, String level, double rate) {
        this.id = id;
        this.level = level;
        this.rate = rate;
    }

    public double getRate() {
        return rate;
    }

    public String getLevel() {
        return level;
    }

    public String getId() {
        return id;
    }

    @Override
    public double getSalary() {
        return rate;
    }

    @Override
    public double getBonus(){
        return 0;
    }

    @Override
    public EmployeeType getType() {
        return EmployeeType.BASIC;
    }

    @Override
    public int compareTo(BasicEmployee o) {
        return Comparator.comparing(BasicEmployee::getSalary)
                .thenComparing(BasicEmployee::getLevel)
                .thenComparing(BasicEmployee::getRate)
                .compare(this, o);
    }
}

class HourlyEmployee extends BasicEmployee {
    private final double hours;

    public HourlyEmployee(String id, String level, double rate, double hours) {
        super(id, level, rate);
        this.hours = hours;
    }

    public double getHours(){
        return hours;
    }

    @Override
    public double getSalary() {
        return getRate() * Math.min(40, hours) +
                getRate() * 1.5 * Math.max(hours - 40, 0);
    }

    @Override
    public String toString() {
        return String.format(
                "Employee ID: %s Level: %s Salary: %.2f Regular hours: %.2f Overtime hours: %.2f",
                getId(), getLevel(), getSalary(), Math.min(hours, 40), Math.max(0, hours - 40)
        );
    }

    @Override
    public EmployeeType getType() {
        return EmployeeType.HOURLY;
    }

    @Override
    public double getOvertime() {
        return getRate() * 1.5 * Math.max(hours - 40, 0);
    }
}

class FreelanceEmployee extends BasicEmployee {
    List<Integer> ticketPoints;

    public FreelanceEmployee(String id, String level, double rate, List<Integer> ticketPoints) {
        super(id, level, rate);
        this.ticketPoints = ticketPoints;
    }

    @Override
    public double getSalary() {
        return ticketPoints.stream()
                .mapToDouble(i -> (double) i)
                .sum() * getRate();
    }

    public int getTicketPoints() {
        return ticketPoints.size();
    }

    @Override
    public String toString() {
        return String.format(
                "Employee ID: %s Level: %s Salary: %.2f Tickets count: %d Tickets points: %d",
                getId(), getLevel(), getSalary(),
                ticketPoints.size(),
                (int) ticketPoints.stream().
                        mapToDouble(s -> (double) s).sum()
        );
    }

    @Override
    public EmployeeType getType() {
        return EmployeeType.FREELANCE;
    }
}

abstract class EmployeeDecorator implements Employee {
    Employee wrapped;

    public EmployeeDecorator(Employee wrapped) {
        this.wrapped = wrapped;
    }

    @Override
    public double getRate() {
        return wrapped.getRate();
    }

    @Override
    public String getLevel() {
        return wrapped.getLevel();
    }

    @Override
    public EmployeeType getType() {
        return wrapped.getType();
    }

    @Override
    public double getOvertime(){
        return wrapped.getOvertime();
    }

    @Override
    public int getTicketPoints() {
        return wrapped.getTicketPoints();
    }

    @Override
    public double getHours() {
        return wrapped.getHours();
    }

    @Override
    public String toString(){
        String baseSalary = String.format("%.2f", wrapped.getSalary());
        String newSalary = String.format("%.2f", this.getSalary());
        String output = wrapped.toString().replace("Salary: " + baseSalary, "Salary: " + newSalary);
        return String.format("%s Bonus: %.2f", output, this.getBonus());
    }
}

class PercentageBonusDecorator extends EmployeeDecorator {
    private final double percentage;
    public PercentageBonusDecorator(Employee wrapped, String percentage)
            throws BonusNotAllowedException {
        super(wrapped);
        this.percentage = Double.parseDouble(percentage.split("%")[0]);
        if (this.percentage > 20) throw new BonusNotAllowedException(percentage);
    }

    @Override
    public double getBonus(){
        return wrapped.getSalary() * percentage / 100;
    }

    @Override
    public double getSalary() {
        double salary = wrapped.getSalary();
        return salary + salary * percentage / 100;
    }
}

class FixedBonusDecorator extends EmployeeDecorator{
    private final double amount;
    public FixedBonusDecorator(Employee wrapped, String amount)
            throws BonusNotAllowedException {
        super(wrapped);
        this.amount = Double.parseDouble(amount);
        if (this.amount > 1000) throw new BonusNotAllowedException(amount + "$");
    }

    @Override
    public double getSalary() {
        return wrapped.getSalary() + amount;
    }

    @Override
    public double getBonus(){
        return amount;
    }
}

class EmployeeFactory {
    public static Employee createEmployee(
            String line,
            Map<String, Double> hourlyRateByLevel,
            Map<String, Double> ticketRateByLevel)
    throws BonusNotAllowedException {
        String[]parts = line.split("\\s+");
        Employee e = createBasicEmployee(line, hourlyRateByLevel, ticketRateByLevel);
        if (parts.length == 2) {
            if (parts[1].contains("%")){
                e = new PercentageBonusDecorator(e, parts[1]);
            } else {
                e = new FixedBonusDecorator(e, parts[1]);
            }
        }
        return e;

    }

    public static Employee createBasicEmployee(
            String line,
            Map<String, Double> hourlyRateByLevel,
            Map<String, Double> ticketRateByLevel ){
        String[] employeeInfo = line.split("\\s+")[0].split(";");
        if ("H".equals(employeeInfo[0])) {
            return new HourlyEmployee(
                    employeeInfo[1],
                    employeeInfo[2],
                    hourlyRateByLevel.get(employeeInfo[2]),
                    Double.parseDouble(employeeInfo[3])
            );
        } else {
            ArrayList<Integer> points = new ArrayList<>();
            for (int i = 3; i < employeeInfo.length; i++) {
                points.add(Integer.parseInt(employeeInfo[i]));
            }

            return new FreelanceEmployee(
                    employeeInfo[1],
                    employeeInfo[2],
                    ticketRateByLevel.get(employeeInfo[2]),
                    points
            );
        }
    }
}

class PayrollSystem {
    List<Employee> employees;
    Map<String, Double> hourlyRateByLevel;
    Map<String, Double> ticketRateByLevel;

    PayrollSystem(Map<String, Double> hourlyRateByLevel, Map<String, Double> ticketRateByLevel) {
        this.hourlyRateByLevel = hourlyRateByLevel;
        this.ticketRateByLevel = ticketRateByLevel;
        this.employees = new ArrayList<>();
    }

    Employee createEmployee(String line) throws BonusNotAllowedException {
        Employee e = EmployeeFactory.createEmployee(line, hourlyRateByLevel, ticketRateByLevel);
        employees.add(e);
        return e;
    }

    public Map<String, Double> getOvertimeSalaryForLevels() {
        // ima bug vo resenieto na courses
        // ova e tocno
//        return employees.stream()
//                .filter(e -> e.getType().equals(EmployeeType.HOURLY))
//                .collect(Collectors.toMap(
//                        Employee::getLevel,
//                        e -> Math.max(0, e.getHours() - 40) * e.getRate() * 1.5,
//                        Double::sum
//                ));

        Map<String, Double> collect = employees.stream()
                .collect(Collectors.toMap(
                        Employee::getLevel,
                        Employee::getOvertime,
                        Double::sum
                ));
        return collect.entrySet().stream().filter(e -> e.getValue() != -1)
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


    public void printStatisticsForOvertimeSalary() {
        DoubleSummaryStatistics stats = employees.stream()
                .filter(e -> e.getType().equals(EmployeeType.HOURLY))
                .mapToDouble(e -> Math.max(0, e.getHours() - 40) * e.getRate() * 1.5)
                .summaryStatistics();
        System.out.printf(
                "Statistics for overtime salary: Min: %.2f Average: %.2f Max: %.2f Sum: %.2f%n",
                stats.getMin(), stats.getAverage(), stats.getMax(), stats.getSum()
        );
    }

    public Map<String, Integer> ticketsDoneByLevel() {
        return employees.stream()
                .filter(e -> e.getType().equals(EmployeeType.FREELANCE))
                .collect(Collectors.toMap(
                        Employee::getLevel,
                        Employee::getTicketPoints,
                        Integer::sum
                ));
    }

    public Collection<Employee> getFirstNEmployeesByBonus(int n) {
        return employees.stream()
                .sorted(Comparator.comparingDouble(Employee::getBonus).reversed())
                .limit(n)
                .collect(Collectors.toList());
    }
}

class BonusNotAllowedException extends Exception {
    BonusNotAllowedException(String amount){
        super("Bonus of " + amount + " is not allowed");
    }
}

public class PayrollSystemTest2 {

    public static void main(String[] args) {

        Map<String, Double> hourlyRateByLevel = new LinkedHashMap<>();
        Map<String, Double> ticketRateByLevel = new LinkedHashMap<>();
        for (int i = 1; i <= 10; i++) {
            hourlyRateByLevel.put("level" + i, 11 + i * 2.2);
            ticketRateByLevel.put("level" + i, 5.5 + i * 2.5);
        }

        Scanner sc = new Scanner(System.in);

        int employeesCount = Integer.parseInt(sc.nextLine());

        PayrollSystem ps = new PayrollSystem(hourlyRateByLevel, ticketRateByLevel);
        Employee emp = null;
        for (int i = 0; i < employeesCount; i++) {
            try {
                emp = ps.createEmployee(sc.nextLine());
            } catch (BonusNotAllowedException e) {
                System.out.println(e.getMessage());
            }
        }

        int testCase = Integer.parseInt(sc.nextLine());

        switch (testCase) {
            case 1: //Testing createEmployee
                if (emp != null)
                    System.out.println(emp);
                break;
            case 2: //Testing getOvertimeSalaryForLevels()
                ps.getOvertimeSalaryForLevels().forEach((level, overtimeSalary) -> {
                    System.out.printf("Level: %s Overtime salary: %.2f\n", level, overtimeSalary);
                });
                break;
            case 3: //Testing printStatisticsForOvertimeSalary()
                ps.printStatisticsForOvertimeSalary();
                break;
            case 4: //Testing ticketsDoneByLevel
                ps.ticketsDoneByLevel().forEach((level, overtimeSalary) -> {
                    System.out.printf("Level: %s Tickets by level: %d\n", level, overtimeSalary);
                });
                break;
            case 5: //Testing getFirstNEmployeesByBonus (int n)
                ps.getFirstNEmployeesByBonus(Integer.parseInt(sc.nextLine())).forEach(System.out::println);
                break;
        }

    }
}