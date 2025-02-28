package it.unibo.iot.serial;

public interface CommChannel {

    /**
     * Send a message represented by a string (without new line).
     * <p>
     * Asynchronous model.
     *
     * @param msg
     */
    void sendMsg(String msg);

    /**
     * To receive a message.
     * <p>
     * Blocking behaviour.
     */
    String receiveMsg() throws InterruptedException;

    /**
     * To check if a message is available.
     *
     * @return
     */
    boolean isMsgAvailable();

}