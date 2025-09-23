class Solution {
    public int compareVersion(String version1, String version2) {
        String[] A = version1.split("\\.");
        String[] B = version2.split("\\.");
        System.out.println(Arrays.toString(A));
        System.out.println(Arrays.toString(B));
        return compare(A, B);
    }

    public int compare(String[] A, String[] B) {
        int n = A.length, m = B.length;
        for(int i = 0; i < Math.min(n, m); i++) {
            int x = Integer.parseInt(A[i]);
            int y = Integer.parseInt(B[i]);
            if(x < y) return -1;
            else if(x > y) return 1;
        }
        if(A.length > B.length) {
            for(int i = Math.min(n, m); i < A.length; i++) {
                if(Integer.parseInt(A[i]) != 0) {
                    return 1;
                }
            }
        } else if(A.length < B.length) {
            for(int i = Math.min(n, m); i < B.length; i++) {
                if(Integer.parseInt(B[i]) != 0) {
                    return -1;
                }
            }
        }
        return 0;
    }
}
