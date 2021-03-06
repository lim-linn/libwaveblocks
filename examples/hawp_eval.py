from WaveBlocksND import *
import numpy.linalg
import numpy.random
import time
import math
import sys

def print_coefficients(wp):
    for node, coeff in zip(list(wp.get_basis_shapes(0).get_node_iterator()), wp.get_coefficients(0)):
        if numpy.linalg.norm(coeff) > 1e-10:
            print node, coeff

def run(D, param_sparsity, param_limit):
    # Number of dimensions
    shape = LimitedHyperbolicCutShape(D,2**(D-param_sparsity) * 3**param_sparsity,[param_limit]*D)
    
    packet = HagedornWavepacket(D,1,0.9)
    
    # PARAMETERS (All components share same parameter set)
    '''
    p = numpy.random.randn(D)
    q = numpy.random.randn(D)
    P = numpy.random.randn(D,D) + 1.0j*numpy.random.randn(D,D)
    Q = numpy.random.randn(D,D) + 1.0j*numpy.random.randn(D,D)
    packet.set_parameters((q,p,Q,P), key=('q','p','Q','P'))
    '''
    
    (p,q,Q,P) = packet.get_parameters(key=('q','p','Q','P'))
    
    for i in range(0,D):
        p[i] += 0.1*numpy.sin(0.9*i)
        q[i] += 0.1*numpy.cos(0.8*i)
        for j in range(0,D):
            P[i,j] += 0.1*numpy.exp(0.7j*(D*i+j))
            Q[i,j] += 0.1*numpy.exp(0.6j*(D*i+j))
    
    packet.set_parameters((q,p,Q,P), key=('q','p','Q','P'))
    
    # SHAPE
    packet.set_basis_shapes((shape),0)
    
    # COEFFICIENTS
    basis_size = shape.get_basis_size()
    '''
    coeffs = numpy.random.randn(basis_size) + 1.0j*numpy.random.randn(basis_size)
    coeffs /= numpy.linalg.norm(coeffs)
    '''
    coeffs = numpy.exp(1j*numpy.arange(basis_size))/math.sqrt(basis_size)
    
    #print coeffs
    
    #for node,coeff in zip(list(packet.get_basis_shapes(0).get_node_iterator()), coeffs):
        #print node, coeff
    
    packet.set_coefficients((coeffs,))
    
    # EVALUATE
    grid = numpy.linspace(-1.0, 1.0,D)
    
    #print packet.get_parameters(key=('q'))[0]
    #print packet.get_parameters(key=('p'))[0]
    #print packet.get_parameters(key=('Q'))[0]
    #print packet.get_parameters(key=('P'))[0]
    
    print "Grid nodes: ", grid
    print "Evaluate wavepacket"
    print "   shape: ", shape
    print "   size of shape: ", shape.get_basis_size()
    
    # SLIM RECURSION
    start = time.clock()
    result = packet.slim_recursion(grid,0)
    end = time.clock()
    
    print "   value (slim): ", result
    print "   time:         ", str((end - start)*1000), "[ms]"
    
    # FAT RECURSION
    start = time.clock()
    result = numpy.dot(packet.get_coefficients(0).T, packet.evaluate_basis_at(grid,0))
    end = time.clock()
    
    print "   value (fat):  ", result
    print "   time:         ", str((end - start)*1000), "[ms]"
    
    #print packet.evaluate_basis_at(grid,0)
    
    print "Evaluate gradient: "
    nabla = packet.get_gradient_operator()
    
    start = time.clock()
    gradobject = nabla.apply_gradient(packet)
    end = time.clock()
    time_construct = (end - start)*1000
    
    start = time.clock()
    result = numpy.zeros((D,1), dtype=complex)
    
    for index, gradwp in enumerate(gradobject):
        if index == 0:
            basis = gradwp.evaluate_basis_at(grid,0)
        result[index,:] = numpy.dot(gradwp.get_coefficients(0).T, basis);
    end = time.clock()
    time_evaluate = (end - start)*1000
    
    print "   value (fat):      ", result.T
    print "   time (construct): ", str(time_construct), "[ms]"
    print "   time (evaluate):  ", str(time_evaluate), "[ms]"
    print ""
    print ""

def main(args):
    if len(args) != 3:
        print "3 arguments required:"
        print "   (1) wavepacket dimensionality D"
        print "   (2) sparsity of basis shape. 0 <= integer value <= D"
        print "   (2) limit of basis shape. integer value > 0"
        print ""
        print "   try example parameters: 5 0 100"
        sys.exit(1)
    
    run(int(args[0]),int(args[1]),int(args[2]))
    
    #for D in range(6,7):
        #for s in range(1,D+1):
            #run(D,s,100)

if __name__ == "__main__":
    numpy.random.seed(0)
    
    main(sys.argv[1:])