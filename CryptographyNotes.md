#Chapter3 Private-Key Encryption

## 3.1 Computational Security


Computational
- take into account computational limits on the attacker (efficient adversary)
- a small probability of failure (adversary can potentially succeedc )

### 3.1.1 Concrete Approach

$(t,\epsilon)$-secure
- if any adversary running for time at most $t$ succeeds in breaking the scheme with probability at most $\epsilon$

### 3.1.2 Asymptotic Approach
asymptotic secure
- any PPT adversary succeeds in breaking the scheme with at most negligible probability (e.g run for $n^3$ mins with probability $2^{40} 2^{-n}$)

negligible
- for every polynomial $p$ and all sufficient large values of $n$ it holds that $f(n) < \frac{1}{p(n)}$
- $negl_3(n) = negl_1(n)+negl_2(n)$ is negligible
- $negl_4(n) = p(n) * negl_1(n)$ is negligible

## 3.2 Defining Computationally Secure Encrytion

private-key encrytion scheme : a tuple of probabilistic polynomial-time algorithms (Gen, Enc, Dec)
- Gen: input $1^n$;  output $k \leftarrow Gen(1^n)$
- Enc: input key $k$ and plaintext $m$ ; output $c \leftarrow Enc_k(m)$
- Dec: input key $k$ and ciphertext $c$; output $m := Dec_k(c)$ or error

### 3.2.1 The Basic Definition of Security

The adversial indistinguishability experiment $PrivK^{eav}_{A,\Pi}(n)$ : [!! **Remember the definition** P54 !!]

EAV-secure (Indistinguishable encrytions in the presence of an eavesdropper)
- $Pr\big[ PrivK^{eav}_{A,\Pi}(n) = 1 \big] \le \frac{1}{2} + negl(n)$
- $|Pr\big[out_A(PrivK^{eav}_{A,\Pi}(n,0))=1\big] - Pr\big[out_A(PrivK^{eav}_{A,\Pi}(n,1))=1\big]| \le negl(n)$

### 3.2.2 *Semantic Security

## 3.3 Constructing Secure Encryption Schemes

### 3.3.1 Pseudorandom Generators and Stream Cipher
Pseudorandom Generator
- Expansion: $\ell(n) > n$
- Pseudorandomness: for PPT $D$, $|Pr[D(G(s))=1]-Pr[D(r)=1]| \le negl(n)$, where G is **deterministic**
- $\ell$ is the expansion factor of G
- Intuitive: an efficient, deterministic algorithm for transforming a short, uniform string (_seed_) into a longer,'uniform-looking' output string (_pseudorandom_)

Seed
- must be chosen uniformly and be kept secret from any adversary
- $s$ must be long enough so that it is not feasible to enumerate all possible seeds

### 3.3.2 UNREAD！！！

## 3.4 Stronger Security Notions

### 3.4.1 Security for Mutiple Encryptions
The multiple-message eavesdropping experiment $PrivK^{mult}_{A,\Pi}(n)$ [Definition Page71]

Indistinguisable multiple encrytions in the presence of an eavesdropper:
-  $Pr\big[ PrivK^{mult}_{A,\Pi}(n) = 1 \big] \le \frac{1}{2} + negl(n)$
- $PrivK^{mult}_{A,\Pi}(n)$ is stronger than $PrivK^{eav}_{A,\Pi}(n)$ 

If $\Pi$ is an encryption scheme with a **deterministic** Enc, than $\Pi$ **cannot** have Indistinguisable multiple encrytions in the presence of an eavesdropper.

### 3.4.2 Chosen-Plaintext Attacks and CPA-Security

The CPA indistinguishability experiment $PrivK^{cpa}_{A,\Pi}(n)$ [Definition Page74]
- Oracle here can be randomized

CPA-secure (Indistinguishable encrytions under a chosen-plaintext attack)
-  $Pr\big[ PrivK^{cpa}_{A,\Pi}(n) = 1 \big] \le \frac{1}{2} + negl(n)$

The LR-oracle experiment $PrivK^{LR-cpa}_{A,\Pi}(n)$ [Definition Page76]

CPA-secure for multiple encryptions (Indistinguishable multiple encrytions under a chosen-plaintext attack)
-  $Pr\big[ PrivK^{LR-cpa}_{A,\Pi}(n) = 1 \big] \le \frac{1}{2} + negl(n)$

CPA-secure $\leftrightarrow$ CPA-secure for multiple encryptions

## 3.5 Constructing CPA-Secure Encryption Schemes

### 3.5.1 Pseudorandom Functions and Block Cipher
$F:\{0,1\}^* \times \{0,1\}^* \rightarrow \{0,1\}^*$
- keyed: the first input is key $k$
- efficient: there is a polynomial-time algorithm that computes $F(k,x)$ given $k,x$
- length-preserving: $\ell_{key}(n)=\ell_{in}(n)=\ell_{out}(n)$

$F_k$ and $f$
- $F_k$ : for uniform $k$; chosen from at most $2^n$ distinct functions
- $f$: chosen uniformly from $Func_n$ ($2^{n·2^n}$ functions)
- $Func_n$: the set of all functions mapping $n$-bits input to $n$-bits output
- $Perm_n$: the set of all functions mapping $n$-bits input to $n$-bits output, where the entries in any two distinct rows must be different ($(2^n)!$ functions)

Pseudorandom function
- the PPT $D$ can query the **deterministic** oracle; $D$ is **not** given the key $k$
- $f \in Func_n$
- $|Pr\big[ D^{F_k(·)}(1^n)=1\big] - Pr\big[ D^{f(·)}(1^n)=1\big]| \le negl(n)$

Pseudorandom permutation
- the PPT $D$ can query the **deterministic** oracle; $D$ is **not** given the key $k$
- $f \in Perm_n$
- $|Pr\big[ D^{F_k(·)}(1^n)=1\big] - Pr\big[ D^{f(·)}(1^n)=1\big]| \le negl(n)$

Strong pseudorandom permutation
- the PPT $D$ can query the **deterministic** oracle; $D$ is **not** given the key $k$
- $f \in Perm_n$
- $|Pr\big[ D^{F_k(·),F^{-1}_k(·)}(1^n)=1\big] - Pr\big[ D^{f(·)，f^{-1}(·)}(1^n)=1\big]| \le negl(n)$

### 3.5.2 CPA-Secure Encryption from Pseudorandom Functions

## 3.6 Modes of Operation

### 3.6.1 Stream-Cipher Modes of Operation
Synchronized mode
- $c:=G_{\infty}(k,1^{|m|})\oplus m$

Unsynchronized mode
- $c:=<IV,G_{\infty}(k,IV,1^{|m|})\oplus m>$

### 3.6.2 Block-Cipher Modes of Operation
Provide a way of encrypting arbitary-length messages using shorter ciphertext
ECB mode (Electronic Code Book)
- $c:=<F_k(m_1),F_k(m_2),...,F_k(m_{\ell})>$
- deterministic; Not EAV-secure; Not CPA-secure

CBC mode (Cipher Block Chaining)
- $c_0 = IV$, $c_i = F_k(c_{i-1}\oplus m_i)$
- Drawbacks
    - must be carried out sequentially
    - chained CBC mode: vulnerable to a CPA attack


OFB mode (Output Feedback)
- $c_i = y_i \oplus m_i$, where  $ y_0:=IV,y_i=F_k(y_{i-1})$
- Advantages
    - It is not required that $F$ be invertible or a permutaion. [ CBC requires that $F$ be invertible ]
    - stateful variant is secure
    -  $y_i$ can be computed in advance which is an advantage compared with CBC
    - If $F$ is PRF, OFB is CPA-secure

CTR mode (Counter)
- $c_i = y_i \oplus m_i$, where  $ y_0:=ctr,y_i=F_k(ctr + i)$
- Advantages
    - It is not required that $F$ be invertible or a permutation. [ CBC requires that $F$ be invertible ]
    - Stateful variant is secure
    -  $y_i$ can be computed in advance 
    - If $F$ is PRF, CTR is CPA-secure : $Pr[PrivK^{cpa}_{A,\Pi}(n)=1] < \frac{1}{2} + \frac{2q(n)^2}{2^n} + negl(n)$ 
    - Encryption and decryption can be fully parallelized
    - It is possible to decrypt the $i$-th block of ciphertext using only a single evaluation of $F$ [ in contrast to OFB ]