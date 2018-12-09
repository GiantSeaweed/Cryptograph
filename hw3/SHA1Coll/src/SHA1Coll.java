import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.UUID;

public class SHA1Coll {
    public static final String Alogrithm = "SHA-1";
    public static final char[] HexDigit  = {'0','1','2','3','4','5','6','7',
                                            '8','9','A','B','C','D','E','F'};
    public static final int TryTimes = 30000000;

    public static void main(String[] args) {
//        System.out.println(commonBit("1111","0000"));
//        System.out.println(commonBit(hex2Bin("1111"),hex2Bin("0000")));
        int maxCommon = 0;
        int curCommon = 0;
        String a="",b="",da="",db="";
        for(int i=0;i<TryTimes;i++ ) {
            String str1 = getRandString();
            String str2 = getRandString();

            String digest1 = encode(Alogrithm, str1);
            String digest2 = encode(Alogrithm, str2);

            curCommon = commonBit(digest1,digest2);
            if( curCommon > maxCommon){
                maxCommon = curCommon;
                a = str1;
                b = str2;
                da = digest1;
                db = digest2;
            }
        }
        System.out.println("Tried " + TryTimes + " times:");
        System.out.println("a: "+a+",  "+"Digest a: "+da);
        System.out.println("b: "+b+",  "+"Digest b: "+db);
        System.out.println("Digest a and Digest b have "+ maxCommon +" bits in common.");
    }

    /**
     * UUID  universally unique ID
     *
     * @return 128-bit random string
     */
    public static String getRandString() {
        UUID uuid = UUID.randomUUID();
        String str = uuid.toString();
        String tmp = str.substring(0, 8) + str.substring(9, 13)
                + str.substring(14, 18) + str.substring(19, 23)
                + str.substring(24);   // remove the '-'
        return tmp;
    }

    /**
     * Encrypt te message with alogrithm to get a digest
     * @param alogrithm
     * @param message
     * @return the digest of message
     */
    public static String encode(String alogrithm, String message) {
        if (alogrithm == null || message == null) {
            return null;
        }
        String digest = message;
        try {
            MessageDigest shaDigest = MessageDigest.getInstance(alogrithm);
            shaDigest.update(message.getBytes());
            digest = byte2Hex(shaDigest.digest());

        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return digest;
    }

    /**
     * Turn te raw bytes to hex format
     * @param bytes
     * @return the hex format string of bytes[]
     */
    public static String byte2Hex(byte[] bytes) {
        int len = bytes.length;
        StringBuffer buffer = new StringBuffer(len * 2);
        for (int i = 0; i < len; i++) {
            buffer.append(HexDigit[(bytes[i] & 0xf0) >> 4]);
            buffer.append(HexDigit[bytes[i] & 0x0f]);
            //System.out.println(bytes[i]/16 +" "+ bytes[i]%16 + " : "+HexDigit[(bytes[i] & 0xf0) >> 4]
            //                             +" "+HexDigit[bytes[i] & 0x0f]) ;
        }
        return buffer.toString();
    }

    public static String hex2Bin(String str){
        int len =str.length();
        StringBuffer buffer = new StringBuffer(len * 4);
        for(int i=0;i<len;i++){
            switch (str.charAt(i)){
                case '0': buffer.append("0000"); break;
                case '1': buffer.append("0001"); break;
                case '2': buffer.append("0010"); break;
                case '3': buffer.append("0011"); break;
                case '4': buffer.append("0100"); break;
                case '5': buffer.append("0101"); break;
                case '6': buffer.append("0110"); break;
                case '7': buffer.append("0111"); break;
                case '8': buffer.append("1000"); break;
                case '9': buffer.append("1001"); break;
                case 'A': buffer.append("1010"); break;
                case 'B': buffer.append("1011"); break;
                case 'C': buffer.append("1100"); break;
                case 'D': buffer.append("1101"); break;
                case 'E': buffer.append("1110"); break;
                case 'F': buffer.append("1111"); break;
                default: break;
            }
        }
        //System.out.println(buffer);
        return buffer.toString();
    }

    public static int commonBit(String str1, String str2){
        if(str1.length() != str2.length())
            return -1;


        //System.out.println(str1+"  length:"+len);
        int counter = 0;
        String str1Bin = hex2Bin(str1);
        String str2Bin = hex2Bin(str2);

        int len = str1Bin.length();
        for(int i=0;i<len;i++){
            if(str1Bin.charAt(i) == str2Bin.charAt(i))
                counter++;
        }
        return counter;
    }
}
