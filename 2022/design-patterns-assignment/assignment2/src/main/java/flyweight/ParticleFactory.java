package flyweight;

import java.util.HashMap;

/**
 *
 * @author kival
 */
public class ParticleFactory {

    private final HashMap<String, Particle> particleHash = new HashMap<>();

    public Particle addParticle(String type, int[] posVec3, int[] speedVec3) {
        Particle p = particleHash.get(type);

        if (p == null) {
            p = new Particle(new byte[65535]); // assume this is 64KB image file that we somehow grabbed from type
            particleHash.put(type, p);
            System.out.println("A " + type + " particle has been created and saved with hash: " + p.hashCode());
        }

        return p;
    }

    // for demo purpose, this is without reusing the same data
    public Particle addNoFlyweightParticle(String type, int[] posVec3, int[] speedVec3) {
        Particle p = new Particle(new byte[65535]);
        System.out.println("A " + type + " particle has been created with hash: " + p.hashCode());

        return p;
    }
}
