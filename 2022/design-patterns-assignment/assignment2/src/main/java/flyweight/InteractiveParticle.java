package flyweight;

import java.util.Arrays;

/**
 *
 * @author kival
 */
// extrinsic state or unique state
// posVec3 and speedVec3 can be changed
public class InteractiveParticle implements IParticle {

    private Particle particle;
    private int[] posVec3;
    private int[] speedVec3;

    public InteractiveParticle(Particle particle, int[] posVec3, int[] speedVec3) {
        this.particle = particle;
        this.posVec3 = posVec3;
        this.speedVec3 = speedVec3;
    }

    public void setPosition(int[] posVec3) {
        this.posVec3 = posVec3;
    }

    public void setSpeed(int[] speedVec3) {
        this.speedVec3 = speedVec3;
    }

    public void draw(String content) {
        particle.draw(content + " with particle hash key " + this.particle.hashCode() + " at " + Arrays.toString(this.posVec3));
    }
;
}
