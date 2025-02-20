class Solution {
    public int minimumCardPickup(int[] a) {
        Map<Integer, Integer> mp = new HashMap<>();
        int ans = 1000000000;
        for(int r = 0, l = 0; r < a.length; r++) {
            add(mp, a[r]);
            while(mp.get(a[r]) > 1) {
                ans = Math.min(ans, r - l + 1);
                del(mp, a[l]);
                l++;
            }
        }
        return ans > a.length ? -1 : ans;
    }
    
    public void add(Map<Integer, Integer> mp, int k) {
        if(mp.containsKey(k)) mp.put(k, mp.get(k) + 1);
        else mp.put(k, 1);
    }
    
    public void del(Map<Integer, Integer> mp, int k) {
        Integer val = mp.get(k);
        if(val == 1) mp.remove(k);
        else mp.put(k, val - 1);
    }
}
