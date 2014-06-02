package com.AiKaiSe.Network;

import java.io.IOException;
import java.lang.Thread.State;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;

import com.AiKaiSe.Values.FunctionCode;

public class ComunicationHandler extends Activity {
	
	private static final String TAG = ComunicationHandler.class.getSimpleName();

	Context myContext;

	long timeStemp = System.currentTimeMillis();
	long limittime = 50; // Send Freuquency limit time .
	int count = 0;
	boolean send = false;
	boolean receive = false;
	String sendbuffer;

	String raspiip = "192.168.1.20";
	int sendport = 8000;
	int receiveport = 8100;

	String sendmessage;

	byte[] sendmessagebytes;

	private long delay = 600; // 200 //Time die ich warte bis ich den Receive
								// Thread schließe
	private Message receivedmessage = null;

	private DatagramSocket rdsocket;
	SharedPreferences preferences;
	
	byte[] debugreceivebytes;

	public ComunicationHandler(Context context) {
		this.myContext = context;
		preferences = PreferenceManager.getDefaultSharedPreferences(context);

	}

	private class SendThread implements Runnable {
		byte[] _sendbuffer;

		public SendThread(byte[] sendbuffer) {
			_sendbuffer = new byte[sendbuffer.length];
			_sendbuffer = sendbuffer;

		}

		@Override
		public void run() {
			try {
				raspiip = preferences.getString("raspiAdress", "n/a");

				InetAddress address = InetAddress.getByName(raspiip);

				sendport = Integer.valueOf(preferences.getString("raspiPort",
						"8000"));

				DatagramPacket packet = new DatagramPacket(_sendbuffer,
						_sendbuffer.length, address, sendport);
				DatagramSocket dsocket = new DatagramSocket();
				Log.d(TAG, "send packet in send Thread ");
				dsocket.send(packet);
				dsocket.close();

			} catch (UnknownHostException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (SocketException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	private class ReceiverThread implements Runnable {
		private int _fc;

		public ReceiverThread(int fc) {
			_fc = fc;
		}

		@Override
		public void run() {
			Log.d(TAG, " start run()");
			byte[] receivemessagebytes = new byte[8192];
			DatagramPacket packet = new DatagramPacket(receivemessagebytes,
					receivemessagebytes.length);

			try {

				rdsocket = new DatagramSocket(receiveport);
				Log.d(TAG, " receive");
				rdsocket.receive(packet);
				rdsocket.close();

			} catch (SocketException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			if (_fc == (((receivemessagebytes[0] << 8) | receivemessagebytes[1]) & 0xFFFFl)
					|| 0xFFFF == (((receivemessagebytes[0] << 8) | receivemessagebytes[1]) & 0xFFFFl)) {
				if ((packet.getLength() - 5) == ((receivemessagebytes[2] << 8) | (receivemessagebytes[3]))) {
					if ((calcChecksume(receivemessagebytes,
							packet.getLength() - 1)) == (receivemessagebytes[packet
							.getLength() - 1])) {

						receivedmessage = new Message();
						receivedmessage.data = new byte[packet.getLength() - 5];
						System.arraycopy(receivemessagebytes, 4,
								receivedmessage.data, 0,
								(packet.getLength() - 5));
						receivedmessage.fc = (int) (((receivemessagebytes[0] << 8) | receivemessagebytes[1]) & 0xFFFFl);
					} else {
						Log.e(TAG,
								"ReceiverThread: Checksum Error");
						Log.e(TAG,
								String.valueOf(calcChecksume(
										receivemessagebytes,
										packet.getLength() - 1))
										+ "--"
										+ (receivemessagebytes[packet
												.getLength() - 1]));
					}
				} else {
					Log.e(TAG,
							"ReceiverThread: Wrong Package Lenght in receive Message");
				}
			} else {
				Log.e(TAG,
						"ReceiverThread: FunctionCode is different to send FunctionCode");
			}
		}
	}

	private Message receive(int fci) throws InterruptedException {
		Log.d(TAG, "receive: called");
		long stemp = System.currentTimeMillis() + delay;
		receivedmessage = null;

		ReceiverThread rthread = new ReceiverThread(fci);
		Thread receivethread = new Thread(rthread);
		receivethread.start();

		while (System.currentTimeMillis() < stemp && receivedmessage == null) { // System.currentTimeMillis()
																				// <
																				// stemp
																				// &&
																				// TODO
																				// einkommentieren
																				// Timeout
			Thread.sleep(10);
			Log.d(TAG,
					"receive: waiting for incomming Message");
		}

		if (receivethread.getState() == State.RUNNABLE) {
			Log.w(TAG,
					"receive: no Message incomming, close Thread now.");
			rdsocket.close();

			if (receivedmessage == null) {
				Log.w(TAG,
						"request: receivemessage == null !!!!");
			}

		}
		return receivedmessage;
	}

	private byte calcChecksume(byte[] array, int length) {

		int cs = 0;
		for (int i = 0; i < length; i++) {
			cs = (cs + (array[i] & 0xFF)) % 0xFF;
		}

		// Log.e("CH", String.valueOf(cs));
		return (byte) cs;
	}

	public void sendFrequency(FunctionCode fc, byte[] dataArray)
			throws IOException {
		if (System.currentTimeMillis() > timeStemp + limittime) {
			Log.d(TAG, "sendfrequency: send");
			timeStemp = System.currentTimeMillis();
			send(fc, dataArray);
		}
	}
	
	public void send(FunctionCode fc, byte[] dataArray) {
		Log.e(TAG, "send: called");
		byte[] buffer;

		if (dataArray == null) {
			buffer = new byte[5];
			buffer[2] = (byte) 0;
			buffer[3] = (byte) 0;

		} else {
			buffer = new byte[dataArray.length + 5];
			buffer[2] = (byte) ((dataArray.length & (0xFF << 8)) >>> 8);
			buffer[3] = (byte) (dataArray.length & 0xFF);

		}

		buffer[0] = (byte) ((fc.getvalue() & (0xFF << 8)) >>> 8); // High Byte
		buffer[1] = (byte) (fc.getvalue() & 0xFF); // Low Byte

		if (dataArray != null) {
			System.arraycopy(dataArray, 0, buffer, 4, dataArray.length);
			buffer[dataArray.length + 4] = calcChecksume(buffer, buffer.length);
		} else {
			buffer[4] = calcChecksume(buffer, buffer.length);

		}

		// anfügen

		SendThread sthread = new SendThread(buffer);
		Thread sendthread = new Thread(sthread);
		sendthread.start();
	}
	
	public Message sendrequest(FunctionCode fc, byte[] dataArray) {
		Log.d(TAG, "sendrequest: called");
		try {

			send(fc, dataArray);
			return receive((fc.getvalue()) | 0x8000);

		} catch (InterruptedException e) {
			Log.e(TAG, "sendrequest: catch Error");
			return null;
		}
	}

}