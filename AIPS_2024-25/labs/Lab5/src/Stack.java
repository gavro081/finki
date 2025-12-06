interface Stack<E> {
    // Elementi na stekot se objekti od proizvolen tip.
// Metodi za pristap:
    public boolean isEmpty();

    public E peek();

    public void clear();

    public void push(E x);

    public E pop();

}
