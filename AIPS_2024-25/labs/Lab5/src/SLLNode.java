class SLLNode<E> {
    protected E element;
    protected SLLNode<E> succ;

    public SLLNode(E element, SLLNode<E> next) {
        this.element = element;
        this.succ = next;
    }
}
