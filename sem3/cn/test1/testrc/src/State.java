class State
{
    public int cId;
    public boolean isRunning;
    public String lastWord;

    State(int cId, String lastWord, boolean isRunning)
    {
        this.cId = cId;
        this.lastWord = lastWord;
        this.isRunning = isRunning;
    }
}
